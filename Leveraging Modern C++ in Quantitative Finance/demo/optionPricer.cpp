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

#include "qf/BSMOptPricer.hpp"
#include "qf/MCEuroOptPricer.hpp"

#include <iostream>

auto main() -> int {
  const Real S = 100.0;
  const Real K = 100.0;
  const Real r = 0.05;
  const Real vol = 0.2;
  const Real T = 1.0;
  const std::size_t m = 250;
  const std::size_t n = 10000;
  const int seed = 0;
  const Real q = 1.0;

  // MCEuroOptPricer x(S, K, r, vol, T, OptionType::Call, m, n, false, seed, q);
  // std::cout << x() << ' ' << x.time() << "ms\n";

  MCEuroOptPricer y(S, K, r, vol, T, OptionType::Put, m, n, true, seed, q);
  std::cout << y() << '\n';
  // std::cout << y() << ' ' << y.time() << "ms\n";

  // BSMOptPricer a(S, K, r, vol, T, OptionType::Call, q);
  // std::cout << a() << ' ' << a.time() << "ms\n";

  // BSMOptPricer b(S, K, r, vol, T, OptionType::Put, q);
  // std::cout << b() << ' ' << b.time() << "ms\n";
}
