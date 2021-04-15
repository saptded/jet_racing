cmake_minimum_required(VERSION 3.17)
project(libserver)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CPP_COMPILER clang)
SET(Boost_USE_STATIC_LIBS OFF)
SET(Boost_USE_MULTITHREAD ON)

set(CMAKE_CXX_FLAGS "-std=c++20 -stdlib=libc++  -Wall  -Wpedantic -fpermissive --coverage")

FIND_PACKAGE(Boost 1.65.1 REQUIRED COMPONENTS system thread regex)
include_directories(SYSTEM ${Boost_INCLUDE_DIRS})

link_libraries(gcov)

include(ExternalProject)
ExternalProject_Add(gtest
        URL https://github.com/google/googletest/archive/release-1.10.0.zip
        PREFIX ${CMAKE_CURRENT_BINARY_DIR}/gtest
        INSTALL_COMMAND ""
        )
ExternalProject_Get_Property(gtest source_dir binary_dir)

enable_testing()
find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIR})


add_library(libserver SHARED  src/hpp/library.hpp src/hpp/AbstractServer.hpp src/hpp/AbstractClient.hpp src/hpp/DataGame.hpp src/cpp/GameServer.cpp src/cpp/GameClient.cpp src/hpp/Position.h)

add_executable(tests src/test/tests.cpp)
add_executable(main src/cpp/library.cpp)

add_test(tests tests)

target_link_libraries(tests PRIVATE GTest::GTest GTest::Main)
target_link_libraries(libserver ${Boost_LIBRARIES})