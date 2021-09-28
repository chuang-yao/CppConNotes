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

#ifndef QF_BISECTION_HPP
#define QF_BISECTION_HPP

#include <cmath>
#include <limits>

namespace qf::root_finder {

using Real = double;

template <typename Func>
auto bisection(
    Func f, Real a, Real b,
    Real tolerance = std::sqrt(std::numeric_limits<Real>::epsilon()),
    const unsigned int maxIterations = 10000,
    Real guessZero = std::sqrt(std::numeric_limits<Real>::epsilon())) {

  // Check that the two inital guesses are not zeroes already
  if (std::abs(f(a)) < guessZero) {
    return a;
  }
  if (std::abs(f(b)) < guessZero) {
    return b;
  }

  if (f(b) * f(a) > 0) {
    // Error condition; must have f(b) * f(a) < 0;
    // otherwise, does not converge:
    return std::numeric_limits<Real>::infinity();
  }

  // Algorithm for bisection method adapted from Numerical Analysis, 5th
  // Edition, Burden and Faires, 1993 and An Introduction to Numerical Analysis,
  // 2nd Eidtion, K. Atkinson, 1989
  for (unsigned int i = 0; i < maxIterations; ++i) {
    Real c = (a + b) / 2;
    if ((std::abs(b - c) / std::abs(b)) < tolerance) {
      return c;
    }
    if (f(b) * f(c) <= 0) {
      a = c;
    } else {
      b = c;
    }
  }

  // Error condition: does not converge:
  return std::numeric_limits<Real>::infinity();
}
} // namespace qf::root_finder

#endif // QF_BISECTION_HPP
