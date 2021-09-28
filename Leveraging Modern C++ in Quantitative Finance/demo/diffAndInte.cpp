#include "qf/Examples.hpp"

#include <boost/math/constants/constants.hpp>
#include <boost/math/differentiation/finite_difference.hpp>
#include <boost/math/quadrature/trapezoidal.hpp>
#include <iostream>

auto main() -> int {

  {
    using namespace boost::math::differentiation;

    std::cout << '\n' << "*** Math - Finite Difference ***" << '\n';

    // Using a lambda:
    auto f = [](Real x) { return exp(x); };
    Real x = 1.7;
    Real dfdx = finite_difference_derivative(f, x);

    std::cout << "(Using a lambda): d/dx exp(" << x << ") = " << dfdx << '\n';

    // Using a function object:
    BoostQuadratic q(0.5, 1.0, 1.0);
    x = 1.0;
    Real dquad = finite_difference_derivative(q, x);
    std::cout << "(Using a function object): d/dx (Boost)Quadratic(" << x
              << ") = " << dquad << '\n';

    std::cout << '\n';
  }

  {
    using namespace boost::math::quadrature;
    using namespace boost::math::double_constants;

    std::cout << '\n' << "*** Math - Numeric Integration ***" << '\n';

    auto f = [](Real x) { return 4.0 / (1.0 + x * x); };

    Real appPi = trapezoidal(f, 0.0, 1.0);

    Real tol = 1e-6;
    int max_refinements = 20;
    Real appPi2 = trapezoidal(f, 0.0, 1.0, tol, max_refinements);

    std::cout << "Trapezoid Rule results for computing pi by integration\n";
    std::cout << "a) with defaults, and b) with tol and max_refine set : \n";
    std::cout << appPi << ", " << appPi2 << "\n\n";

    BoostCubic cubic(-1.0, 1.0, -1.0, 1.0);
    Real cubeInt = trapezoidal(cubic, 0.0, 2.0, tol, max_refinements);
    std::cout << "Trapezoid Rule results for computing integral of cubic "
                 "polynomial: \n";
    std::cout << cubeInt << "\n\n";

    SineFunction sf(1.0, 1.0, 0.0);
    std::cout << "Trapezoid Rule results for computing integral of simple\n";
    std::cout << "sine function on 0 to 2pi (note the use of the Boost two_pi "
                 "constant):\n";
    Real sineInt = trapezoidal(sf, 0.0, two_pi, tol, max_refinements);
    std::cout << sineInt << "\n\n";

    auto psf = std::make_unique<SineFunction>(1.0, 1.0, 0.0);
    std::cout << "Trapezoid Rule results for computing integral of simple\n";
    std::cout
        << "sine function on 0 to 2pi, with unique_ptr to the function:\n";
    Real pSineInt = trapezoidal(*psf, 0.0, two_pi);
    std::cout << pSineInt << "\n\n";

    // NOTE:  Added the section from here to end of the function
    // AFTER original sample code was released to the class, CFRM 524 Summer
    // 2018.
    std::vector<std::unique_ptr<RealFunction>> vfcns;
    vfcns.push_back(std::make_unique<SineFunction>(1.0, 1.0, 0.0));
    vfcns.push_back(std::make_unique<BoostCubic>(-1.0, 1.0, -1.0, 1.0));

    // Real w = trapezoidal((*vfcns.at(0)), 0.0, two_pi);	// Not supported
    //(trapezoidal is compile-time only)

    // Need to trick it with a lambda:
    std::cout << "Trapezoid Rule results for computing integral of simple\n";
    std::cout << "sine function on 0 to 2pi, as polymorphic function object:\n";
    auto g = [&vfcns](Real x) { return (*vfcns.at(0))(x); };

    Real vecUnqPtrFcn = trapezoidal(g, 0.0, two_pi);
    std::cout << vecUnqPtrFcn << '\n';

    std::cout << '\n';
  }
}
