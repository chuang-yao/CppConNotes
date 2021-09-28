if((UNIX AND (NOT APPLE)) AND (CMAKE_CXX_COMPILER_ID STREQUAL "Clang"))
  add_compile_options(-stdlib=libc++)
  add_link_options(-stdlib=libc++)
endif()

add_executable(block block.cpp)
add_executable(join join.cpp)
add_executable(mutex mutex.cpp)
add_executable(thread thread.cpp)

target_link_libraries(block pthread)
target_link_libraries(join pthread)
target_link_libraries(mutex pthread)
target_link_libraries(thread pthread)
