cmake_minimum_required(VERSION 3.13)
project(jet_racing)
set(CMAKE_CXX_STANDARD 17)

find_package(GTest REQUIRED)
find_package(SFML 2.5 COMPONENTS graphics REQUIRED)
set(ALL_LIBS presenter sfml-graphics)

add_subdirectory(libs)
add_subdirectory(tests)

add_executable(main mainMenu.cpp)
target_link_libraries(main PUBLIC ${ALL_LIBS})
