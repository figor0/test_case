cmake_minimum_required(VERSION 3.5)

project(test_task LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(test_task main.cpp profile.h test_runner.h)
