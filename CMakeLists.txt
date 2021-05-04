cmake_minimum_required(VERSION 3.17)
project(libserver)


set(CMAKE_CXX_STANDARD 20)
SET(Boost_USE_STATIC_LIBS OFF)
SET(Boost_USE_MULTITHREAD ON)

set(CMAKE_CXX_FLAGS "-std=c++20  -fpermissive --coverage  -v  -Wall -Werror ")
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

find_package(fmt REQUIRED)
find_package(restinio REQUIRED)


add_library(libclient SHARED src/client/GameClient.cpp src/client/AbstractClient.hpp)
include_directories(libclient src/client)

add_library(libdata_struct INTERFACE src/data_structs/DataGame.hpp  src/data_structs/Position.hpp src/data_structs/Connection.hpp)
include_directories(libdata_struct src/data_structs)

add_library(libserver SHARED src/server/AbstractServer.hpp  src/server/GameServer.cpp)
include_directories(libserver src/server)

add_executable(tests src/test/tests.cpp)
add_executable(main src/library.cpp)


add_test(tests tests)
target_link_libraries(libserver  libdata_struct)
target_link_libraries(libclient libdata_struct)
target_link_libraries(main PRIVATE libserver libclient libdata_struct)
target_link_libraries(tests PRIVATE GTest::GTest GTest::Main)
target_link_libraries(libserver ${Boost_LIBRARIES} fmt::fmt restinio::restinio)
