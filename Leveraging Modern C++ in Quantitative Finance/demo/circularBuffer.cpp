#include <qf/TimeSeries.hpp>

#include <iostream>

auto main() -> int {

  {
    std::cout << '\n' << "*** Circular Buffer ***" << '\n';
    boost::circular_buffer<int> cb(3);

    // Insert threee elements into the buffer.
    cb.push_back(1);
    cb.push_back(2);
    cb.push_back(3);

    int a = cb[0]; // a == 1
    int b = cb[1]; // b == 2
    int c = cb[2]; // c == 3

    std::cout << "Our buffer initially contains " << a << ", " << b << ", and "
              << c << '\n';

    // The buffer is full now, so pushing subsequent
    // elements will overwrite the front-most elements.

    cb.push_back(4); // Overwrite 1 with 4.
    cb.push_back(5); // Overwrite 2 with 5.

    // The buffer now contains 3, 4 and 5.  Note we can also use the at(.)
    // function.
    a = cb.at(0); // a == 3
    b = cb.at(1); // b == 4
    c = cb.at(2); // c == 5

    std::cout << "After pushing back 4 and 5 into our buffer, we now have: "
              << a << ", " << b << ", and " << c << '\n';

    // Elements can be popped from either the front or the back.
    cb.pop_back();  // 5 is removed.
    cb.pop_front(); // 3 is removed.

    // Leaving only one element with value = 4.
    int d = cb[0]; // d == 4

    std::cout << "After popping off the front and back elements, we are left "
                 "with a buffer of size "
              << cb.size() << ", and lone element = " << d << '\n';

    std::cout << '\n';
  }

  {
    std::cout << '\n' << "*** Circular Buffer - Time Series ***" << '\n';

    std::vector<Real> vts = {0.0, 1.0, 2.0, 3.0, 4.0, 5.0,
                             6.0, 7.0, 8.0, 9.0, 10.0};
    TimeSeries ts(vts);

    std::cout << "Value in 3rd element (idx = 2) is " << ts.value(2) << '\n';
    std::cout << "Value in last element (idx = 10) is " << ts.value(10) << '\n';

    std::cout << "ma of last 3 elements = " << ts.movingAvg(3) << '\n';
    std::cout << "ma of all elements = " << ts.movingAvg() << '\n';
    std::cout << "vol of all elements = " << ts.volatility() << '\n';

    ts.append(25.0);
    std::cout << "Append 25 to the end ...\n";

    std::cout << "1st element is now " << ts.value(0) << '\n';
    std::cout << "last element is now " << ts.value(10) << '\n';
    std::cout << "ma of all elements = " << ts.movingAvg() << '\n';
    std::cout << "vol of all elements = " << ts.volatility() << '\n';

    std::cout << '\n';
  }
}