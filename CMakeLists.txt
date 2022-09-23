cmake_minimum_required(VERSION 3.5)
project(simple_forecaster)

set(CMAKE_CXX_STANDARD 14)

add_executable(simple_forecaster main.cpp include/SimpleForecaster.cpp include/SimpleForecaster.h)
