#ifndef QF_EUROTREE_HPP
#define QF_EUROTREE_HPP

#include "qf/EuroNode.hpp"
#include "qf/OptionType.hpp"

#include <boost/multi_array.hpp>

class EuroTree {
public:
  EuroTree(Real mktPrice, Real mktRate, Real mktVol, Real divRate, Real strike,
           Real expiry, OptionType porc, int numTimePoints);

  auto resetMktPrice(Real newMktPrice) -> Real;
  auto resetMktRate(Real newMktRate) -> Real;
  auto resetDivRate(Real newDivRate) -> Real;
  auto resetMktVol(Real newMktVol) -> Real;

  [[nodiscard]] auto optionPrice() const -> Real;
  [[nodiscard]] auto calcDelta(Real pctShift = 0.0001) const -> Real;

  // Accessors:
  [[nodiscard]] auto operator()(std::size_t i, std::size_t j) const -> EuroNode;
  [[nodiscard]] auto grid() const -> boost::multi_array<EuroNode, 2>;

private:
  // Mkt Data:
  Real mktPrice_; // Market price for underlying security
  Real mktRate_;  // Risk-free rate
  Real mktVol_;   // Volatility

  // Product/Contract Data:
  Real divRate_;    // Dividend rate
  Real strike_;     // Strike price
  Real expiry_;     // Time to expiration as a year fraction
  OptionType porc_; // Put or Call enum class

  // Model Settings:
  std::size_t numTimePoints_;
  // const DayCount& dayCount_;
  // Stored as reference to handle polymorphic object

  // Calculated member variables:
  boost::multi_array<EuroNode, 2> grid_;
  Real dt_, u_, d_, p_; // delta t, u, d, and p parameters, a la James book
  Real discFctr_;    // Discount factor (fixed for each time step, a la James)
  Real optionPrice_; // Store result as member

  // 5th Real value will be time value (replaces two dates)
  std::tuple<Real, Real, Real, Real, Real, OptionType, int> data_;

  // Helper functions:
  void calcPrice_(); // This function refactors the next five into one call
  void gridSetup_();
  void paramInit_(); // Determine delta t, u, d, and p, a la James book
  void projectPrices_();
  void calcPayoffs_();
};

#endif // QF_EUROTREE_HPP

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
