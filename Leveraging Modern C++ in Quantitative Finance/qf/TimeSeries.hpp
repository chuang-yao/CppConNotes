#ifndef QF_TIMESERIES_HPP
#define QF_TIMESERIES_HPP

#include <boost/circular_buffer.hpp>
#include <vector>

using Real = double;

class TimeSeries {
public:
  explicit TimeSeries(std::size_t length);
  explicit TimeSeries(boost::circular_buffer<Real> ts);
  explicit TimeSeries(const std::vector<Real> &ts);

  void append(Real x);
  [[nodiscard]] auto value(std::size_t k) const -> Real;
  [[nodiscard]] auto buffer() const -> boost::circular_buffer<Real>;

  [[nodiscard]] auto movingAvg(std::size_t t = 0) const -> Real;
  [[nodiscard]] auto volatility(std::size_t t = 0) const -> Real;

private:
  boost::circular_buffer<Real> ts_;
  [[nodiscard]] auto mean_(std::size_t t = 0) const -> Real;
};

#endif // QF_TIMESERIES_HPP

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
