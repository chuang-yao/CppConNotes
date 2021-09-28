#include "qf/BSMOptPricer.hpp"
#include "qf/OptionType.hpp"

#include <boost/math/distributions.hpp>
#include <chrono>
#include <cmath>
#include <limits>

BSMOptPricer::BSMOptPricer(Real spot, Real strike, Real riskFreeRate,
                           Real volatility, Real timeToExpiry,
                           OptionType optionType, Real quantity)
    : spot_(spot), strike_(strike), riskFreeRate_(riskFreeRate),
      volatility_(volatility), timeToExpiry_(timeToExpiry), porc_(optionType),
      quantity_(quantity) {
  price_ = 0.0;
  time_ = 0.0;
  calculate_();
}

auto BSMOptPricer::optionPrice() const -> Real { return price_; }

auto BSMOptPricer::calcDelta() const -> Real {
  boost::math::normal normDist;
  Real d1 = (std::log(spot_ / strike_) +
             (riskFreeRate_ + volatility_ * volatility_ / 2) * timeToExpiry_) /
            (std::sqrt(timeToExpiry_) * volatility_);
  if (porc_ == OptionType::Call) {
    return boost::math::cdf(normDist, d1);
  }
  if (porc_ == OptionType::Put) {
    return -boost::math::cdf(normDist, -d1);
  }
  return std::numeric_limits<Real>::quiet_NaN();
}

auto BSMOptPricer::operator()() const -> Real { return this->optionPrice(); }

auto BSMOptPricer::time() const -> Real { return time_; }

// Real normalCDF(Real x) { return std::erfc(-x / std::sqrt(2)) / 2; }
// does not take infinity into account

void BSMOptPricer::computePrice_() {
  Real d1 = (std::log(spot_ / strike_) +
             (riskFreeRate_ + volatility_ * volatility_ / 2) * timeToExpiry_) /
            (std::sqrt(timeToExpiry_) * volatility_);
  Real d2 = d1 - std::sqrt(timeToExpiry_) * volatility_;

  boost::math::normal stdNormDist;

  switch (porc_) {
  case OptionType::Call:
    price_ = spot_ * boost::math::cdf(stdNormDist, d1) -
             std::exp(-riskFreeRate_ * timeToExpiry_) * strike_ *
                 boost::math::cdf(stdNormDist, d2);
    price_ = price_ * quantity_;
    break;
  case OptionType::Put:
    price_ = -spot_ * boost::math::cdf(stdNormDist, -d1) +
             std::exp(-riskFreeRate_ * timeToExpiry_) * strike_ *
                 boost::math::cdf(stdNormDist, -d2);
    price_ = price_ * quantity_;
    break;
  default: // This should never happen
    price_ = std::numeric_limits<Real>::quiet_NaN();
    break;
  }
}

void BSMOptPricer::calculate_() {
  {
    auto b = std::chrono::steady_clock::now();
    computePrice_();
    auto e = std::chrono::steady_clock::now();
    time_ = static_cast<Real>(
        std::chrono::duration_cast<std::chrono::milliseconds>(e - b).count());
  }
}
