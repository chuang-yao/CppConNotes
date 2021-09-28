#include "qf/EquityPriceGenerator.hpp"

#include <limits>
#include <random>
#include <stdexcept>

EquityPriceGenerator::EquityPriceGenerator(Real initEquityPrice,
                                           std::size_t numTimeSteps,
                                           Real timeToExpiry, Real drift,
                                           Real volatility)
    : dt_(timeToExpiry / static_cast<double>(numTimeSteps)),
      initEquityPrice_(initEquityPrice), numTimeSteps_(numTimeSteps),
      drift_(drift), volatility_(volatility) {
  if (numTimeSteps_ == std::numeric_limits<std::size_t>::max()) {
    throw std::invalid_argument("Too many steps in one simulation!");
  }
}

auto EquityPriceGenerator::operator()(int seed) const -> std::vector<Real> {
  std::vector<Real> v;
  v.reserve(numTimeSteps_ + 1);
  v.push_back(initEquityPrice_);

  Real equityPrice = initEquityPrice_;
  std::mt19937_64 mtEngine(seed);
  std::normal_distribution nd;

  auto getNextPrice = [this](Real currentPrice, Real normDist) {
    Real expArg1 = (drift_ - (volatility_ * volatility_) / 2) * dt_;
    Real expArg2 = volatility_ * sqrt(dt_) * normDist;
    return currentPrice * exp(expArg1 + expArg2);
  };

  for (std::size_t i = 0; i != numTimeSteps_; ++i) {
    equityPrice = getNextPrice(equityPrice, nd(mtEngine));
    v.push_back(equityPrice);
  }

  return v; // RVO
}
