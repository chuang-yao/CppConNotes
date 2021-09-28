#ifndef QF_MCEUROOPTPRICER_HPP
#define QF_MCEUROOPTPRICER_HPP

#include "qf/OptionType.hpp"

#include <vector>

using Real = double;

class MCEuroOptPricer {
public:
  MCEuroOptPricer(Real spot, Real strike, Real riskFreeRate, Real volatility,
                  Real timeToExpiry, OptionType porc, std::size_t numTimeSteps,
                  std::size_t numScenarios, bool runParallel, int initSeed,
                  Real quantity);

  [[nodiscard]] auto optionPrice() const -> Real;
  [[nodiscard]] auto calcDelta(Real pctShift = 0.0001) const -> Real;

  [[nodiscard]] auto operator()() const -> Real;
  [[nodiscard]] auto time() const -> Real;

private:
  void calculate_();

  // private helper functions
  void computePrice_();
  void generateSeeds_();
  auto payoff_(Real termPrice) -> Real;

  // compare results
  void computePriceNoParallel_();
#ifdef _WIN32
  void computePriceWithAsync_();
#else
  void computePriceWithPool_();
#endif

  // model inputs
  Real spot_;
  Real strike_;
  Real riskFreeRate_;
  Real volatility_;
  Real timeToExpiry_;
  OptionType porc_;

  std::size_t numTimeSteps_;
  std::size_t numScenarios_;
  bool runParallel_;
  int initSeed_;

  Real quantity_;

  // computed values
  Real discFactor_;
  Real price_;

  // generated seeds for MC scenarios
  std::vector<int> seeds_;

  // runtime comparison using concurrency
  Real time_;
};

#endif // QF_MCEUROOPTPRICER_HPP

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
