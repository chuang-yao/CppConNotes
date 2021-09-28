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

#include "qf/Bisection.hpp"
#include "qf/Steffenson.hpp"

#include <cmath>
#include <iostream>

using qf::root_finder::Real;

using qf::root_finder::bisection;
using qf::root_finder::steffenson;

class Quadratic {
public:
  auto operator()(Real x) const -> Real { return x * x + 3.0 * x + 2.0; };
};
class SineFcn {
public:
  auto operator()(Real x) const -> Real { return sin(x); };
};

auto main() -> int {

  {
    std::cout << '\n' << "*** Bisection Method ***" << '\n';

    // First, represent functions as function objects:
    Quadratic qdrf;
    SineFcn sf;

    auto qdrRoot = bisection(qdrf, -3.0, -1.5, 0.0001, 1000);
    auto sinRoot = bisection(sf, -1.0, 3.0);

    std::cout << "Passing function objects:" << '\n';
    std::cout << "Root of quadratic function = " << qdrRoot << '\n';
    std::cout << "Root of sine function = " << sinRoot << '\n' << '\n';

    // Passing function objects // (both OK):
    // Root of quadratic function = -2
    // Root of sine function = 1.52815e-162 -- essentially zero

    // Next, use lambdas:
    auto cubic = [](Real x) { return x * x * x + 1; };       // , -10.0, 0.0)
    auto powSeven = [](Real x) { return std::pow(x, 7.0); }; // , -3.0, 3.0)

    auto cubicRoot = bisection(cubic, -10.0, 3.0, 0.0001, 1000);
    // Put in larger tolerance and fewer max iterations, to demonstrate:
    auto powRoot = bisection(powSeven, -3.0, 3.0, 0.0001, 100);
    std::cout << "Passing lambda expressions:" << '\n';
    std::cout << "Root of cubic function = " << cubicRoot << '\n';
    std::cout << "Root of power function = " << powRoot << '\n';

    // Passing lambda expressions // (both OK):
    // Root of cubic function = -1
    // Root of power function = 7.44402e-24 -- essentially zero

    std::cout << '\n';
  }

  {
    std::cout << '\n' << "*** Steffenson Method ***" << '\n';

    // First, represent functions as function objects:
    Quadratic qdr;
    SineFcn sf;

    auto qdrRoot = steffenson(qdr, -1.5);
    auto sinRoot = steffenson(sf, -0.5);

    std::cout << "Passing function objects:" << '\n';
    std::cout << "Root of quadratic function = " << qdrRoot << '\n';
    std::cout << "Root of sine function = " << sinRoot << '\n' << '\n';

    // Passing function objects :
    // Root of quadratic function = -2
    // Root of sine function = 1.52815e-162 -- essentially zero

    // Next, use lambdas:
    auto cubic = [](Real x) { return x * x * x + 1; };      // , -10.0, 0.0)
    auto logFcn = [](Real x) { return std::log(x - 3.5); }; // , -3.0, 3.0)

    auto cubRoot = steffenson(cubic, -10.0);
    // Put in larger tolerance and fewer max iterations, to demonstrate:
    auto logRoot = steffenson(logFcn, 5.0, 0.001, 1000000);
    std::cout << "Passing lambda expressions:" << '\n';
    std::cout << "Root of cubic function = " << cubRoot << '\n';
    std::cout << "Root of std::log function = " << logRoot << '\n' << '\n';

    // Passing lambda expressions :
    // Root of cubic function = -1
    // Root of std::log function = 4.5
  }
}
