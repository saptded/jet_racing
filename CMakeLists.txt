cmake_minimum_required(VERSION 3.16)
project(jet_racing)
set(CMAKE_CXX_STANDARD 17)

add_subdirectory(libs)

find_package(SFML 2.5 COMPONENTS graphics audio REQUIRED)

add_executable(main2 mainMenu.cpp)
target_link_libraries(main2 PUBLIC presenter model response observer racer mechanicalValues sfml-graphics)