#include "qf/EuroTree.hpp"
#include "qf/Examples.hpp"

#include <exception>
#include <iostream>

auto main() -> int {

  {
    std::cout << '\n' << "*** Multi Array - Lattice ***" << '\n';

    // boost::extents in 2D represent number of rows and columns
    // in the generic matrix; ie, extents[numRows][numCols].
    boost::multi_array<TestClassForMultiArray, 2> mtx{boost::extents[4][6]};

    // 1st quick test:  compiles and runs OK
    mtx[0][0].calc(3.0, 4.0);

    // Populate the old fashioned way with a loop.
    // Use the mutator calc(Real, Real) to
    // set each element.  Note: the shape() method
    // on boost::multi_array gives us access to the
    // bounds on each dimension (rows and columns
    // (in the 2D matrix case).
    for (std::size_t i = 0; i < 4; ++i) {
      for (std::size_t j = 0; j < 6; ++j) {
        mtx[i][j].calc(static_cast<Real>(i), static_cast<Real>(j));
      }
    }

    // Verify element type (TestClass):
    std::cout << mtx[1][1]() << ' ' << typeid(mtx[1][1]).name() << '\n';

    // Display all elements, in one row, but using std::for_each(.):
    // avoid pointer arithmetic
    /*
        std::for_each(
            mtx.data(), mtx.data() + mtx.num_elements(),
            [](const TestClassForMultiArray &tc) { std::cout << tc() << ' '; });
        std::cout << '\n';
     */
    std::cout << '\n';
  }

  {
    std::cout << '\n' << "*** Multi Array - Lattice Pricing ***" << '\n';

    EuroTree myTree(100.0, 0.10, 0.2, 0.04, 100.0, 0.5, OptionType::Call, 4);

    std::cout << '\n'
              << "Display terminal underlying and payoff prices:" << '\n';
    for (auto i = 3; i >= 0; --i) {
      std::cout << i << ": " << myTree(i, 3).underlying << ", "
                << myTree(i, 3).payoff << '\n';
    }

    std::cout << '\n' << "Convergence to Black-Scholes-Merton Model:" << '\n';
    EuroTree callTree(100.0, 0.05, 0.2, 0.0, 100.0, 1.0, OptionType::Call,
                      1000);
    std::cout << callTree.optionPrice() << ", " << callTree.calcDelta(0.0001)
              << '\n';
    EuroTree putTree(100.0, 0.05, 0.2, 0.0, 100.0, 1.0, OptionType::Put, 1000);
    std::cout << putTree.optionPrice() << ", " << putTree.calcDelta(0.0001)
              << '\n';

    std::cout << '\n';
  }

  {
    EuroTree myTree(100.0, 0.10, 0.2, 0.04, 100.0, 0.5, OptionType::Call, 4);
    try {
      myTree.resetMktVol(-0.2);

    } catch (std::exception &e) {
      std::cout << e.what() << '\n';
    }
  }
}