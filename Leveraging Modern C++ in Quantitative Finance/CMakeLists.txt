cmake_minimum_required(VERSION 3.15.0)

project("Leveraging Modern C++ in Quantitative Finance"
  VERSION 0.2.0)

include_directories("${CMAKE_CURRENT_SOURCE_DIR}")

find_package(Boost REQUIRED)
find_package(Threads REQUIRED)

add_subdirectory(demo)
add_subdirectory(qf)
