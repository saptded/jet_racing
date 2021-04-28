cmake_minimum_required(VERSION 3.17)
project(libserver)

SET(Boost_USE_STATIC_LIBS OFF)
SET(Boost_USE_MULTITHREAD ON)

set(CMAKE_CXX_FLAGS "-Wall  -Wpedantic -fpermissive --coverage  -v")
include(ExternalProject)

ExternalProject_Add(
        boost
        PREFIX ${CMAKE_CURRENT_BINARY_DIR}/boost
        URL "https://dl.bintray.com/boostorg/release/1.76.0/source/boost_1_76_0.tar.gz"
        GIT_TAG "Boost_1_76_0"
        CONFIGURE_COMMAND ""
        BUILD_COMMAND bjam --with-regex toolset=gcc variant=debug link=static install --prefix=${CMAKE_CURRENT_BINARY_DIR}/boostinstall
        BUILD_IN_SOURCE 1
        INSTALL_COMMAND ""
)

FIND_PACKAGE(Boost 1.76.0 REQUIRED COMPONENTS system thread regex)
include_directories(SYSTEM ${Boost_INCLUDE_DIRS})

link_libraries(gcov)

ExternalProject_Add(gtest
        URL https://github.com/google/googletest/archive/release-1.10.0.zip
        PREFIX ${CMAKE_CURRENT_BINARY_DIR}/gtest
        INSTALL_COMMAND ""
        )
ExternalProject_Get_Property(gtest source_dir binary_dir)

enable_testing()
find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIR})


add_library(libserver SHARED  src/hpp/library.hpp src/hpp/AbstractServer.hpp src/hpp/AbstractClient.hpp src/hpp/DataGame.hpp src/cpp/GameServer.cpp src/cpp/GameClient.cpp src/hpp/Position.h src/hpp/ServerDataConnection.h)

add_executable(tests src/test/tests.cpp)
add_executable(main src/cpp/library.cpp)

add_test(tests tests)

target_link_libraries(tests PRIVATE GTest::GTest GTest::Main)
target_link_libraries(libserver ${Boost_LIBRARIES})