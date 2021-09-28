#include <algorithm>
#include <boost/accumulators/accumulators.hpp>
#include <boost/accumulators/statistics/max.hpp>
#include <boost/accumulators/statistics/mean.hpp>
#include <boost/accumulators/statistics/min.hpp>
#include <boost/accumulators/statistics/stats.hpp>
#include <boost/accumulators/statistics/variance.hpp>
#include <boost/bind/bind.hpp>
#include <boost/ref.hpp>
#include <iostream>
#include <vector>

using Real = double;

auto main() -> int {

  {
    using namespace boost::accumulators;

    std::cout << '\n' << "*** Accumulator - Min & Max ***" << '\n';
    accumulator_set<Real, features<tag::min, tag::max>> acc;
    // push in some data . . .
    acc(5.8);
    acc(-1.7);
    acc(2.9);
    // Display the range
    std::cout << '(' << extract::min(acc) << ", " << extract::max(acc) << ")\n";
  }

  {
    using namespace boost::accumulators;

    std::cout << '\n' << "*** Accumulator - Mean & Variance ***" << '\n';
    accumulator_set<Real, features<tag::mean, tag::variance>> acc;
    // push in some data . . .
    acc(1.2);
    acc(2.3);
    acc(3.4);
    acc(4.5);
    // Display the range
    std::cout << '(' << extract::mean(acc) << ", " << extract::variance(acc)
              << ")\n";
  }

  {
    using namespace boost::accumulators;
    using namespace boost::placeholders;

    std::cout << '\n'
              << "*** Accumulator - Working with std::vector ***" << '\n';
    std::vector<Real> v{-0.7196, -3.5214, 16.3332, 19.5379,
                        2.6357,  5.1342,  -7.4481};

    accumulator_set<Real, features<tag::min, tag::max>> acc;

    // Just know this pattern; scope with boost::
    // std::for_each(v.cbegin(), v.cend(), boost::bind<void>(boost::ref(acc),
    // _1));
    std::for_each(v.cbegin(), v.cend(), [&](Real x) { acc(x); });

    // Display the range (same as before):
    std::cout << '(' << extract::min(acc) << ", " << extract::max(acc) << ")\n";

    std::cout << '\n';
  }
}
