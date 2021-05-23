cmake_minimum_required(VERSION 3.13)
project(jet_racing)
set(CMAKE_CXX_STANDARD 17)

set(CMAKE_CXX_FLAGS "-fpermissive --coverage  -v  -fPIE -fconcepts")

add_compile_options(-fPIE)
include(FetchContent)
FetchContent_Declare(
        restinio
        URL https://github.com/Stiffstream/restinio/releases/download/v.0.6.13/restinio-0.6.13-full.zip

)
FetchContent_MakeAvailable(restinio)

add_subdirectory(${restinio_SOURCE_DIR}/dev/fmt ${restinio_BINARY_DIR}/fmt)
add_subdirectory(${restinio_SOURCE_DIR}/dev/nodejs/http_parser ${restinio_BINARY_DIR}/http_parser)
add_subdirectory(${restinio_SOURCE_DIR}/dev ${restinio_BINARY_DIR})

add_library(restiniofull INTERFACE)

target_link_libraries(restiniofull INTERFACE restinio::restinio)
target_include_directories(restiniofull INTERFACE ${restinio_SOURCE_DIR}/dev/asio/include)
target_compile_options(restiniofull INTERFACE -fPIE -fPIC)




add_subdirectory(libs)

find_package(SFML 2.5 COMPONENTS graphics audio REQUIRED)

add_executable(main myMain.cpp)
target_link_libraries(main PUBLIC restiniofull presenter model response observer racer mechanicalValues sfml-graphics libserver libclient libdata_struct libserialization)
