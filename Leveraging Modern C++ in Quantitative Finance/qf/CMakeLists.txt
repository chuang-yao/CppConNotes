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

add_library(qf STATIC
  BSMOptPricer.cpp
  BSMOptPricer.hpp
  EquityPriceGenerator.cpp
  EquityPriceGenerator.hpp
  EuroNode.hpp
  EuroTree.cpp
  EuroTree.hpp
  MCEuroOptPricer.cpp
  MCEuroOptPricer.hpp
  OptionType.hpp
  TimeSeries.cpp
  TimeSeries.hpp
)

if(Boost_FOUND)
  target_include_directories(qf SYSTEM PUBLIC "${Boost_INCLUDE_DIRS}")
endif()

if(Threads_FOUND)
  target_link_libraries(qf PUBLIC Threads::Threads)
endif()
