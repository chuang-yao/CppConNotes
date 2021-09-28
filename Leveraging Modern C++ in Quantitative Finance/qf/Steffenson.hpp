/*
        Copyright 2019 Daniel Hanson, Tania Luo

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

#ifndef QF_STEFFENSON_HPP
#define QF_STEFFENSON_HPP

#include <cmath>
#include <limits>

namespace qf::root_finder {

using Real = double;

template <typename Func>
auto steffenson(
    Func f, Real initialGuess,
    Real tolerance = std::sqrt(std::numeric_limits<Real>::epsilon()),
    const unsigned int maxIterations = 10000,
    Real guessZero = std::sqrt(std::numeric_limits<Real>::epsilon())) {

  // check whether the initial guess is already a root of the target function
  if (std::abs(f(initialGuess)) < guessZero) {
    return initialGuess;
  }

  Real x_n_1 = initialGuess;
  Real x_n = 0.0;

  for (unsigned int i = 0; i < maxIterations; ++i) {
    // Formula for Steffensen's method
    // An Introduction to Numerical Analysis, 2nd ed., Atkinson 1989
    Real D = f(x_n_1 + f(x_n_1)) - f(x_n_1);
    x_n = x_n_1 - ((f(x_n_1) * f(x_n_1)) / D);
    if (std::abs(x_n_1 - x_n) < tolerance) {
      return x_n;
    }
    x_n_1 = x_n;
  }

  return std::numeric_limits<Real>::infinity();
}

} // namespace qf::root_finder

#endif // QF_STEFFENSON_HPP
