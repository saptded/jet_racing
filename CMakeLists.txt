cmake_minimum_required(VERSION 3.19)
project(test)



set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_FLAGS "--coverage  -v  -Wall  -std=c++20")
add_subdirectory(jet_racing/src/lib)
include(FetchContent)
FetchContent_Declare(cpr GIT_REPOSITORY https://github.com/whoshuu/cpr.git GIT_TAG c8d33915dbd88ad6c92b258869b03aba06587ff9) # the commit hash for 1.5.0
FetchContent_MakeAvailable(cpr)

find_package(fmt REQUIRED)
find_package(restinio REQUIRED)

add_executable(main main.cpp)

target_link_libraries(main PRIVATE restinio::restinio fmt::fmt cpr::cpr  libserver libclient libdata_struct)
