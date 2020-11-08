cmake_minimum_required(VERSION 3.10)
project(CityTrafficSimulator_ZPR)

enable_testing()
find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})

file(GLOB_RECURSE SOURCES LIST_DIRECTORIES true *.h *.cpp)
