cmake_minimum_required(VERSION 3.17)
project(libserver)

set(CMAKE_CXX_FLAGS "-fpermissive --coverage  -v  -fconcepts")

link_libraries(gcov)

add_subdirectory(src/lib)

