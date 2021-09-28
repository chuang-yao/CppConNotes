#include "qf/TimeSeries.hpp"

#include <cmath>
#include <numeric>

using boost::circular_buffer;

TimeSeries::TimeSeries(std::size_t length)
    : ts_(circular_buffer<Real>(length)) {}

TimeSeries::TimeSeries(boost::circular_buffer<Real> ts) : ts_(std::move(ts)) {}

TimeSeries::TimeSeries(const std::vector<Real> &ts) {
  ts_.set_capacity(ts.size());
  std::copy(ts.begin(), ts.end(), back_inserter(ts_));
}

void TimeSeries::append(Real x) { ts_.push_back(x); }

auto TimeSeries::value(std::size_t k) const -> Real { return ts_.at(k); }

auto TimeSeries::buffer() const -> boost::circular_buffer<Real> { return ts_; }

auto TimeSeries::movingAvg(std::size_t t) const -> Real {
  std::size_t offset = 0;
  if ((0 < t) && (t < ts_.size())) {
    offset = ts_.size() - t;
  } else {
    t = ts_.size();
  }
  return std::accumulate(ts_.begin() + offset, ts_.end(), 0.0) /
         static_cast<Real>(t);
}

auto TimeSeries::volatility(std::size_t t) const -> Real {
  std::size_t offset = 0;
  if ((0 < t) && (t < ts_.size())) {
    offset = ts_.size() - t;
  } else {
    t = ts_.size();
  }
  return std::sqrt(std::inner_product(ts_.begin() + offset, ts_.end(),
                                      ts_.begin() + offset, 0.0) /
                       static_cast<Real>(t) -
                   mean_(t) * mean_(t));
}

auto TimeSeries::mean_(std::size_t t) const -> Real {
  std::size_t offset = 0;
  if ((0 < t) && (t < ts_.size())) {
    offset = ts_.size() - t;
  } else {
    t = ts_.size();
  }
  return std::accumulate(ts_.begin() + offset, ts_.end(), 0.0) /
         static_cast<Real>(t);
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
