#include "qf/EuroTree.hpp"
#include "qf/OptionType.hpp"

#include <algorithm>
#include <cmath>
#include <limits>
#include <stdexcept>

using std::exp;
using std::make_tuple;
using std::max;
using std::min;
using std::sqrt;
using std::tuple;

EuroTree::EuroTree(Real mktPrice, Real mktRate, Real mktVol, Real divRate,
                   Real strike, Real expiry, OptionType porc, int numTimePoints)
    : mktPrice_(mktPrice), mktRate_(mktRate), mktVol_(mktVol),
      divRate_(divRate), strike_(strike), expiry_(expiry), porc_(porc),
      numTimePoints_(numTimePoints) {
  dt_ = u_ = d_ = p_ = discFctr_ = optionPrice_ = 0.0;
  calcPrice_();
}

auto EuroTree::optionPrice() const -> Real { return optionPrice_; }

auto EuroTree::calcDelta(Real pctShift) const -> Real {
  if (pctShift == 0) {
    throw std::invalid_argument(
        "Non-zero price change required to compute delta");
  }
  EuroTree uTree(*this); // tree if mktPrice does up
  EuroTree dTree(*this); // tree if mkrPrice does downn
  Real delta = (uTree.resetMktPrice(mktPrice_ * (1 + pctShift)) -
                dTree.resetMktPrice(mktPrice_ * (1 - pctShift))) /
               (2 * pctShift * mktPrice_);
  return delta;
}

auto EuroTree::operator()(std::size_t i, std::size_t j) const -> EuroNode {
  return grid_[i][j];
}

auto EuroTree::grid() const -> boost::multi_array<EuroNode, 2> { return grid_; }

auto EuroTree::resetMktPrice(Real newMktPrice) -> Real {
  if (newMktPrice < 0) {
    throw std::invalid_argument(
        "Reset failed. Market price should be non-negative.");
  }
  if (newMktPrice != mktPrice_) {
    mktPrice_ = newMktPrice;
    calcPrice_();
  }
  return optionPrice_;
}

auto EuroTree::resetMktRate(Real newMktRate) -> Real {
  if (newMktRate != mktRate_) {
    mktRate_ = newMktRate;
    calcPrice_();
  }
  return optionPrice_;
}

auto EuroTree::resetDivRate(Real newDivRate) -> Real {
  if (newDivRate < 0) {
    throw std::invalid_argument(
        "Reset failed. Stock dividend should be non-negative.");
  }
  if (newDivRate != divRate_) {
    divRate_ = newDivRate;
    calcPrice_();
  }
  return optionPrice_;
}

auto EuroTree::resetMktVol(Real newMktVol) -> Real {
  if (newMktVol < 0) {
    throw std::invalid_argument(
        "Reset failed. Market volatility should be non-negative.");
  }
  if (newMktVol != mktVol_) {
    mktVol_ = newMktVol;
    calcPrice_();
  }
  return optionPrice_;
}

void EuroTree::calcPrice_() {
  paramInit_();
  gridSetup_();
  projectPrices_();
  calcPayoffs_();
  optionPrice_ = this->operator()(0, 0).payoff;
}

void EuroTree::paramInit_() {
  // Real yfToExpiry = dayCount_(valueDate_, expireDate_);
  dt_ = expiry_ / (static_cast<Real>(numTimePoints_) - 1.0);
  u_ = exp(mktVol_ * sqrt(dt_));
  d_ = 1.0 / u_;
  p_ = (exp((mktRate_ - divRate_) * dt_) - d_) / (u_ - d_);
  discFctr_ = exp(-mktRate_ * dt_);
}

void EuroTree::gridSetup_() {
  grid_.resize(boost::extents[numTimePoints_][numTimePoints_]);
}

void EuroTree::projectPrices_() {
  grid_[0][0].underlying = mktPrice_;

  for (std::size_t j = 1; j < numTimePoints_; ++j) {
    for (std::size_t i = 0; i <= j; ++i) {
      if (i < j) {
        grid_[i][j].underlying = d_ * grid_[i][j - 1].underlying;
      } else {
        grid_[i][j].underlying = u_ * grid_[i - 1][j - 1].underlying;
      }
    }
  }
}

void EuroTree::calcPayoffs_() {
  auto payoff = [this](Real underlying) {
    if (porc_ == OptionType::Call) {
      return max(underlying - strike_, 0.0);
    }
    return max(strike_ - underlying, 0.0);
  };

  for (std::size_t j = numTimePoints_ - 1;; --j) {
    for (std::size_t i = 0; i <= j; ++i) {
      if (j == numTimePoints_ - 1) {
        grid_[i][j].payoff = payoff(grid_[i][j].underlying);
      } else {
        grid_[i][j].payoff = discFctr_ * (p_ * grid_[i + 1][j + 1].payoff +
                                          (1.0 - p_) * grid_[i][j + 1].payoff);
      }
    }
    if (j == 0) {
      break;
    }
  }
}

/*
        Copyright 2019 Daniel Hanson

        Licensed under the Apache License, Version 2.0 (the "License");
        you may not use this file except in compliance with the License.
        You may obtain a copy of the License at

                http://www.apache.org/licenses/LICENSE-2.0

        Unless required by applicable law or agreed to in writing, software
        distributed under the License is distributed on an "AS IS" BASIS,
        WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
        See the License for the specific language governing permissions and
        limitations under the License.
*/
