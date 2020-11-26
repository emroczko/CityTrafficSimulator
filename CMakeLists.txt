cmake_minimum_required(VERSION 3.1)
project(CityTrafficSimulator)

set(CMAKE_CXX_STANDARD 14)

set(SFML_DIR "External Libraries/Windows/SFML/lib/cmake/SFML")

find_package(SFML 2.5 COMPONENTS graphics REQUIRED)




#Bring the headers, such as Student.h into the project
include_directories(Code)

#However, the file(GLOB...) allows for wildcard additions:
file(GLOB SOURCES "Code/*.cpp")

add_executable(CityTrafficSimulator ${SOURCES})
target_link_libraries(CityTrafficSimulator sfml-graphics)