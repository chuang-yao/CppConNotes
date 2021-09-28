set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if(MSVC)
  add_compile_options(/W3 /WX)
else()
  add_compile_options(-Wall -Wextra -Wpedantic -Werror)
endif()

if((UNIX AND (NOT APPLE)) AND (CMAKE_CXX_COMPILER_ID STREQUAL "Clang"))
  add_compile_options(-stdlib=libc++)
  add_link_options(-stdlib=libc++ -lc++abi)
endif()

link_libraries(qf)

add_executable(circularBuffer circularBuffer.cpp)
add_executable(optionPricer optionPricer.cpp)
add_executable(diffAndInte diffAndInte.cpp)
add_executable(optionDelta optionDelta.cpp)
add_executable(latticeMethod latticeMethod.cpp)
add_executable(rootFinder rootFinder.cpp)
add_executable(statAccumulator statAccumulator.cpp)
