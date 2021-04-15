cmake_minimum_required(VERSION 3.16)
project(libmap CXX)

set(CMAKE_CXX_STANDARD 20)

set(CMAKE_CXX_FLAGS "-Wall -Wpedantic -Werror")

add_library(map STATIC project/src/Map.cpp)
target_include_directories(map PUBLIC project/include)

add_library(element STATIC project/src/Element.cpp)
target_include_directories(element PUBLIC project/include)

add_executable(libmap project/src/main.cpp)
target_link_libraries(libmap map element)

find_package(GTest REQUIRED)
set(SOURCES tests/run_tests.cpp tests/tests.cpp)
add_executable(runTests ${SOURCES})
target_link_libraries(runTests GTest::gtest map)