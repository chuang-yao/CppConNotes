#ifndef QF_EQUITYPRICEGENERATOR_HPP
#define QF_EQUITYPRICEGENERATOR_HPP

#include <vector>

using Real = double;

class EquityPriceGenerator {
public:
  EquityPriceGenerator(Real initEquityPrice, std::size_t numTimeSteps,
                       Real timeToExpiry, Real drift, Real volatility);

  [[nodiscard]] auto operator()(int seed) const -> std::vector<Real>;

private:
  const Real dt_;
  const Real initEquityPrice_;
  const std::size_t numTimeSteps_;
  const Real drift_;
  const Real volatility_;
};

#endif // QF_EQUITYPRICEGENERATOR_HPP
