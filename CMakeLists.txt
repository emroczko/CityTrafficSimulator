cmake_minimum_required(VERSION 3.1)

project(CityTrafficSimulator)


set(CMAKE_CXX_STANDARD 14)

set(SFML_DIR "External Libraries/Windows/SFML/lib/cmake/SFML")

find_package(Catch2 REQUIRED)


find_package(SFML 2.5 COMPONENTS graphics REQUIRED)


include_directories(Code)
include_directories(Code/Tests)


file(GLOB SOURCES "Code/*.cpp")
file(GLOB TESTS "Code/Tests/*.cpp")


add_executable(CityTrafficSimulator ${SOURCES} ${TESTS})

target_link_libraries(CityTrafficSimulator sfml-graphics)

target_link_libraries(CityTrafficSimulator Catch2::Catch2)

include(CTest)
include(Catch)
catch_discover_tests(CityTrafficSimulator)