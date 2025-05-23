cmake_minimum_required(VERSION 3.10)
project(HirschbergAligner)

set(CMAKE_CXX_STANDARD 11)

# Main program
add_executable(hirschberg_main src/main.cpp src/hirschberg.cpp)

# GoogleTest
enable_testing()
find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})
include_directories(src)

add_executable(hirschberg_test test/hirschberg_test.cpp src/hirschberg.cpp)
target_link_libraries(hirschberg_test ${GTEST_LIBRARIES} pthread)

add_test(NAME HirschbergTest COMMAND hirschberg_test) 