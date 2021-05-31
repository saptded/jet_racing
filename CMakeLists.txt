cmake_minimum_required(VERSION 3.16)
project(jet_racing)
set(CMAKE_CXX_STANDARD 17)

set(CMAKE_CXX_FLAGS "-fpermissive --coverage  -v  -fPIE -fconcepts")

add_compile_options(-fPIE -fPIC)
include(FetchContent)
include(ExternalProject)
FetchContent_Declare(
        restinio
        URL https://github.com/Stiffstream/restinio/releases/download/v.0.6.13/restinio-0.6.13-full.zip

)
FetchContent_MakeAvailable(restinio)

FetchContent_Declare(cpr GIT_REPOSITORY https://github.com/whoshuu/cpr.git GIT_TAG c8d33915dbd88ad6c92b258869b03aba06587ff9)
FetchContent_MakeAvailable(cpr)

ExternalProject_Add(
        rapidjson
        PREFIX "vendor/rapidjson"
        GIT_REPOSITORY "https://github.com/Tencent/rapidjson.git"
        GIT_TAG f54b0e47a08782a6131cc3d60f94d038fa6e0a51
        TIMEOUT 10
        CMAKE_ARGS
        -DRAPIDJSON_BUILD_TESTS=OFF
        -DRAPIDJSON_BUILD_DOC=OFF
        -DRAPIDJSON_BUILD_EXAMPLES=OFF
        CONFIGURE_COMMAND ""
        BUILD_COMMAND ""
        INSTALL_COMMAND ""
        UPDATE_COMMAND ""
)

ExternalProject_Get_Property(rapidjson source_dir)
set(RAPIDJSON_INCLUDE_DIR ${source_dir}/include)
include_directories(${RAPIDJSON_INCLUDE_DIR})
include_directories(
        ${CMAKE_SOURCE_DIR}/include
        ${GFLAGS_INCLUDE_DIR}
        ${BENCHMARK_INCLUDE_DIR}
        ${RAPIDJSON_INCLUDE_DIR}
)

add_subdirectory(${restinio_SOURCE_DIR}/dev/fmt ${restinio_BINARY_DIR}/fmt)
add_subdirectory(${restinio_SOURCE_DIR}/dev/nodejs/http_parser ${restinio_BINARY_DIR}/http_parser)
add_subdirectory(${restinio_SOURCE_DIR}/dev ${restinio_BINARY_DIR})

add_library(restiniofull INTERFACE)

target_link_libraries(restiniofull INTERFACE restinio::restinio)
target_include_directories(restiniofull INTERFACE ${restinio_SOURCE_DIR}/dev/asio/include)
target_compile_options(restiniofull INTERFACE -fPIE -fPIC)




add_subdirectory(libs)

find_package(SFML 2.5 COMPONENTS graphics audio REQUIRED)

add_executable(main mainMenu.cpp)
add_dependencies(main rapidjson)
target_link_libraries(main PUBLIC restiniofull sfGameViewer presenter model response observer racer mechanicalValues sfml-graphics cpr::cpr libserver libclient libdata_struct libcustomDeserialization libserialization libcustomRequest libstartServer menu)