cmake_minimum_required(VERSION 3.1)

project(CityTrafficSimulator)

option(BUILD_TESTS "Build tests" OFF)

if(BUILD_TESTS)
include("cmakeTest.txt")
else()
include("cmakeRun.txt")

endif(BUILD_TESTS)

unset(BUILD_TESTS)


