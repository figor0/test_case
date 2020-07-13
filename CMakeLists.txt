cmake_minimum_required(VERSION 3.5)

project(test_task LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

add_executable(${PROJECT_NAME} main.cpp profile.hpp test_runner.hpp filter.hpp)

set(test_source test.cpp)

enable_testing()
add_executable(unit_test ${test_source} profile.hpp test_runner.hpp filter.hpp)
add_test(all_unit unit_test)
