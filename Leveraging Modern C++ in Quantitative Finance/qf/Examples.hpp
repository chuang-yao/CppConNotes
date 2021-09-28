#ifndef QF_EXAMPLES_HPP
#define QF_EXAMPLES_HPP

#include <cmath>

using Real = double;

class TestClassForMultiArray {
public:
  void calc(Real x, Real y) { result_ = x * y; }
  auto operator()() const -> Real { return result_; }

private:
  Real result_;
};

class RealFunction {
public:
  RealFunction() = default;
  RealFunction(const RealFunction &) = default;
  RealFunction(RealFunction &&) = default;
  auto operator=(const RealFunction &) -> RealFunction & = default;
  auto operator=(RealFunction &&) -> RealFunction & = default;
  virtual ~RealFunction() = default;

  [[nodiscard]] virtual auto operator()(Real x) const -> Real = 0;
  [[nodiscard]] virtual auto fcnValue(Real x) const -> Real = 0;
};

// Classes BoostQuadratic and BoostCubic are used for the Boost
// numerical differentiation and trapezoid method integration
// examples.  There are also quadratic and cubic function examples
// in RootFindingExamples.cpp, but these are different.  At a
// later date, these will be consolidated.

class BoostQuadratic : public RealFunction {
public:
  // ax^2 + bx + c

  BoostQuadratic(Real a, Real b, Real c) : a_(a), b_(b), c_(c) {}

  [[nodiscard]] auto operator()(Real x) const -> Real override {
    return fcnValue(x);
  }
  [[nodiscard]] auto fcnValue(Real x) const -> Real override {
    return x * (a_ * x + b_) + c_;
  }

private:
  Real a_ = 1.0, b_ = 1.0, c_ = 1.0;
};

class BoostCubic : public RealFunction {
public:
  // ax^3 + bx2 + cx + d

  BoostCubic(Real a, Real b, Real c, Real d) : a_(a), b_(b), c_(c), d_(d) {}

  [[nodiscard]] auto operator()(Real x) const -> Real override {
    return fcnValue(x);
  }
  [[nodiscard]] auto fcnValue(Real x) const -> Real override {
    return x * x * (a_ * x + b_) + c_ * x + d_;
  }

private:
  Real a_ = 1.0, b_ = 1.0, c_ = 1.0, d_ = 1.0;
};

class SineFunction : public RealFunction {
public:
  SineFunction(Real a, Real b, Real c) : a_(a), b_(b), c_(c) {}

  [[nodiscard]] auto operator()(Real x) const -> Real override {
    return fcnValue(x);
  }
  [[nodiscard]] auto fcnValue(Real x) const -> Real override {
    return a_ * std::sin(b_ * x + c_);
  }

private:
  Real a_ = 1.0, b_ = 1.0, c_ = 1.0;
};

#endif // QF_EXAMPLES_HPP

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
