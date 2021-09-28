include_directories("${CMAKE_CURRENT_SOURCE_DIR}")

find_package(Boost REQUIRED)
find_package(Threads REQUIRED)

add_subdirectory(demo)
add_subdirectory(qf)
