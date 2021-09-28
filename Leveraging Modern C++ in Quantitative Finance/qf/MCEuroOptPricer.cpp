#include "qf/MCEuroOptPricer.hpp"
#include "qf/EquityPriceGenerator.hpp"

#include <chrono>
#include <cmath>
#include <limits>
#include <numeric>
#include <vector>

#ifdef _WIN32
#include <future>
#else
#include <boost/asio.hpp>
#endif

MCEuroOptPricer::MCEuroOptPricer(Real spot, Real strike, Real riskFreeRate,
                                 Real volatility, Real timeToExpiry,
                                 OptionType porc, std::size_t numTimeSteps,
                                 std::size_t numScenarios, bool runParallel,
                                 int initSeed, Real quantity)
    : spot_(spot), strike_(strike), riskFreeRate_(riskFreeRate),
      volatility_(volatility), timeToExpiry_(timeToExpiry), porc_(porc),
      numTimeSteps_(numTimeSteps), numScenarios_(numScenarios),
      runParallel_(runParallel), initSeed_(initSeed), quantity_(quantity) {
  discFactor_ = std::exp(-riskFreeRate_ * timeToExpiry_);
  price_ = 0.0;
  time_ = 0.0;
  calculate_();
}

auto MCEuroOptPricer::optionPrice() const -> Real { return price_; }

auto MCEuroOptPricer::calcDelta(Real pctShift) const -> Real {
  if (pctShift != 0) {
    MCEuroOptPricer u(*this);
    MCEuroOptPricer d(*this);
    u.spot_ = spot_ * (1 + pctShift);
    d.spot_ = spot_ * (1 - pctShift);
    u.calculate_();
    d.calculate_();
    Real delta = (u() - d()) / (2 * pctShift * spot_);
    return delta;
  }
  return std::numeric_limits<Real>::quiet_NaN();
}

auto MCEuroOptPricer::operator()() const -> Real { return this->optionPrice(); }

auto MCEuroOptPricer::time() const -> Real { return time_; }

void MCEuroOptPricer::calculate_() {
  auto b = std::chrono::steady_clock::now();
  computePrice_();
  auto e = std::chrono::steady_clock::now();
  time_ = static_cast<Real>(
      std::chrono::duration_cast<std::chrono::milliseconds>(e - b).count());
}

// private helper functions

// compute the option price
void MCEuroOptPricer::computePrice_() {
  if (runParallel_) {
#ifdef _WIN32
    computePriceWithAsync_();
#else
    computePriceWithPool_();
#endif
  } else {
    computePriceNoParallel_();
  }
}

// single-threaded implementation
void MCEuroOptPricer::computePriceNoParallel_() {
  EquityPriceGenerator epg(spot_, numTimeSteps_, timeToExpiry_, riskFreeRate_,
                           volatility_);
  generateSeeds_();

  std::vector<Real> discountedPayoffs;
  discountedPayoffs.reserve(numScenarios_);

  for (auto &seed : seeds_) {
    Real terminalPrice = (epg(seed)).back();
    Real payoff = payoff_(terminalPrice);

    discountedPayoffs.push_back(discFactor_ * payoff);
  }

  Real numScens = static_cast<Real>(numScenarios_);
  price_ =
      quantity_ * (1.0 / numScens) *
      std::accumulate(discountedPayoffs.begin(), discountedPayoffs.end(), 0.0);
}

#ifdef _WIN32
// multithreading with std::async
// std::async is currently pooled on Windows 10, but NOT on UNIX-like systems
void MCEuroOptPricer::computePriceWithAsync_() {
  EquityPriceGenerator epg(spot_, numTimeSteps_, timeToExpiry_, riskFreeRate_,
                           volatility_);
  generateSeeds_();

  std::vector<std::future<std::vector<Real>>> futures;
  futures.reserve(numScenarios_);

  for (auto &seed : seeds_) {
    futures.push_back(std::async(epg, seed));
  }

  std::vector<Real> discountedPayoffs;
  discountedPayoffs.reserve(numScenarios_);

  for (auto &future : futures) {
    Real terminalPrice = future.get().back();
    Real payoff = payoff_(terminalPrice);
    discountedPayoffs.push_back(discFactor_ * payoff);
  }

  Real numScens = static_cast<Real>(numScenarios_);
  price_ =
      quantity_ * (1.0 / numScens) *
      std::accumulate(discountedPayoffs.begin(), discountedPayoffs.end(), 0.0);
}
#else
// multithreading with boost::asio::thread_pool
void MCEuroOptPricer::computePriceWithPool_() {
  EquityPriceGenerator epg(spot_, numTimeSteps_, timeToExpiry_, riskFreeRate_,
                           volatility_);
  generateSeeds_();

  std::vector<Real> discountedPayoffs;
  discountedPayoffs.reserve(numScenarios_);
  std::mutex mtx;

  boost::asio::thread_pool pool(std::thread::hardware_concurrency());
  for (auto &seed : seeds_) {
    boost::asio::post(pool, [&]() {
      Real terminalPrice = (epg(seed)).back();
      Real payoff = payoff_(terminalPrice);
      std::lock_guard lock(mtx);
      discountedPayoffs.push_back(discFactor_ * payoff);
    });
  }
  pool.join();

  Real numScens = static_cast<Real>(numScenarios_);
  price_ =
      quantity_ * (1.0 / numScens) *
      std::accumulate(discountedPayoffs.begin(), discountedPayoffs.end(), 0.0);
}
#endif

void MCEuroOptPricer::generateSeeds_() {
  seeds_.resize(numScenarios_);
  std::iota(seeds_.begin(), seeds_.end(), initSeed_);
}

auto MCEuroOptPricer::payoff_(Real termPrice) -> Real {
  switch (porc_) {
  case OptionType::Call:
    return std::max(termPrice - strike_, 0.0);
  case OptionType::Put:
    return std::max(strike_ - termPrice, 0.0);
  default: // This case should NEVER happen
    return std::numeric_limits<Real>::quiet_NaN();
  }
}

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
