cmake_minimum_required(VERSION 3.13)
project(jet_racing)
set(CMAKE_CXX_STANDARD 17)

add_subdirectory(libs)

find_package(SFML 2.5 COMPONENTS graphics REQUIRED)

add_executable(main main.cpp)
target_link_libraries(main PUBLIC controller model modelResponse observer racer utils sfml-graphics response viewer viewerSourceRacer viewerSource)
