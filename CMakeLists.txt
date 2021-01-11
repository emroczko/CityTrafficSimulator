cmake_minimum_required(VERSION 3.1)

project(CityTrafficSimulator)

option(BUILD_RUN "Build run" OFF)

if(BUILD_RUN)
include("cmakeRun.txt")
else()
include("cmakeTest.txt")

endif(BUILD_RUN)

unset(BUILD_RUN)


