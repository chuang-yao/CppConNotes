#ifndef QF_BSMOPTPRICER_HPP
#define QF_BSMOPTPRICER_HPP

#include "qf/OptionType.hpp"

using Real = double;

class BSMOptPricer {
public:
  BSMOptPricer(Real spot, Real strike, Real riskFreeRate, Real volatility,
               Real timeToExpiry, OptionType optionType, Real quantity);

  [[nodiscard]] auto optionPrice() const -> Real;
  [[nodiscard]] auto calcDelta() const -> Real;

  [[nodiscard]] auto operator()() const -> Real;
  [[nodiscard]] auto time() const -> Real;

private:
  void calculate_();
  void computePrice_();

  // model inputs
  Real spot_;
  Real strike_;
  Real riskFreeRate_;
  Real volatility_;
  Real timeToExpiry_;
  OptionType porc_;

  Real quantity_;

  // computed values
  Real price_;

  // runtime comparison using concurrency
  Real time_;
};

#endif // QF_BSMOPTPRICER_HPP
