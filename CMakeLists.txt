cmake_minimum_required(VERSION 3.13)
project(jet_racing)
set(CMAKE_CXX_STANDARD 17)

add_subdirectory(libs)

find_package(SFML 2.5 COMPONENTS graphics audio REQUIRED)

add_executable(main mainMenu.cpp)
#target_link_libraries(main PUBLIC presenter model response observer racer mechanicalValues sfml-graphics)
target_link_libraries(main PUBLIC menu presenter model response observer racer mechanicalValues sfml-graphics)