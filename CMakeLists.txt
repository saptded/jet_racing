cmake_minimum_required(VERSION 3.17)
project(libserver)


set(CMAKE_CXX_STANDARD 20)
SET(Boost_USE_STATIC_LIBS OFF)
SET(Boost_USE_MULTITHREAD ON)

set(CMAKE_CXX_FLAGS "-fpermissive --coverage  -v  -Wall -Werror ")
include(ExternalProject)


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

add_subdirectory(src/lib)

add_executable(tests src/test/tests.cpp)
add_executable(main src/library.cpp)


add_test(tests tests)

target_link_libraries(main PRIVATE libserver libclient libdata_struct)
target_link_libraries(tests PRIVATE GTest::GTest GTest::Main  libserver libclient libdata_struct)
