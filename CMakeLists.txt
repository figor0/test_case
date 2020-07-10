cmake_minimum_required(VERSION 3.5)

project(test_task LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

add_executable(${PROJECT_NAME} main.cpp profile.h test_runner.h filter.h)

set(test_source test.cpp)

enable_testing()

add_executable(unit_test ${test_source} profile.h test_runner.h filter.h)

add_test(all_unit unit_test)
