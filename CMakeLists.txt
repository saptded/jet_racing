cmake_minimum_required(VERSION 3.13)
project(jet_racing)
set(CMAKE_CXX_STANDARD 17)

set(CMAKE_CXX_FLAGS "-Wall -Wpedantic -Werror")

add_subdirectory(libs)

add_executable(main main.cpp)
target_link_libraries(main PUBLIC map element)

find_package(GTest REQUIRED)
set(SOURCES tests/run_tests.cpp tests/tests.cpp)
add_executable(runTests ${SOURCES})
target_link_libraries(runTests GTest::gtest map element)