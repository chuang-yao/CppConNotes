# Notes on "Leveraging Modern C++ in Quantitative Finance" by Daniel Hanson at CppCon 2019


## Monte-Carlo Simulation with Task-based Concurrency

`std::async` works as intended on Windows 10 but has significant performance downfall in UNIX-like systems such as macOS and Linux. This is because the implementation of `std::async` on Windows reuses threads created and behaves like a thread pool; it does not on UNIX-like platforms, which incurrs great overhead by calling `pthread_create` for every single simulation. Read [this artical](https://ddanilov.me/std-async-implementations/) by Dmitry Danilov for more details. 

Similar performance can be achieved by using the thread pool from the `boost` library. 


## Performance of Pseudo Random Number Generation by the Standard Library

`std::normal_distribution` with `std::mt19937_64` has different performance across popular toolchains. `MSVC` is the slowest; `gcc` and `clang` are both about 50% faster with `clang` pulling slightly ahead. 

Note that when using `clang`, one should link against `libc++` instead of `libstdc++` for full performance. 