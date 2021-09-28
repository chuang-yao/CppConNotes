#include "qf/BSMOptPricer.hpp"
#include "qf/EuroTree.hpp"
#include "qf/MCEuroOptPricer.hpp"
#include "qf/OptionType.hpp"

#include <iostream>

auto main() -> int {
  {
    std::cout << '\n' << "*** Lattice Method ***" << '\n';

    EuroTree x(100.0, 0.05, 0.2, 0.0, 100.0, 1.0, OptionType::Call, 1000);
    EuroTree y(100.0, 0.05, 0.2, 0.0, 100.0, 1.0, OptionType::Put, 1000);

    std::cout << x.optionPrice() << '\t' << x.calcDelta() << '\n';
    std::cout << y.optionPrice() << '\t' << y.calcDelta() << '\n';

    std::cout << '\n';
  }

  {
    std::cout << '\n' << "*** Monte-Carlo Method ***" << '\n';

    MCEuroOptPricer x(100.0, 100.0, 0.05, 0.2, 1.0, OptionType::Call, 250,
                      10000, true, 0, 1.0);
    MCEuroOptPricer y(100.0, 100.0, 0.05, 0.2, 1.0, OptionType::Put, 250, 10000,
                      true, 0, 1.0);

    std::cout << x.optionPrice() << '\t' << x.calcDelta() << '\n';
    std::cout << y.optionPrice() << '\t' << y.calcDelta() << '\n';

    std::cout << '\n';
  }

  {
    std::cout << '\n' << "*** Black-Scholes-Merton Model ***" << '\n';

    BSMOptPricer x(100.0, 100.0, 0.05, 0.2, 1.0, OptionType::Call, 1.0);
    BSMOptPricer y(100.0, 100.0, 0.05, 0.2, 1.0, OptionType::Put, 1.0);

    std::cout << x.optionPrice() << '\t' << x.calcDelta() << '\n';
    std::cout << y.optionPrice() << '\t' << y.calcDelta() << '\n';

    std::cout << '\n';
  }
}
