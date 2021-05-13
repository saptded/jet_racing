cmake_minimum_required(VERSION 3.19)
project(jet_racing)
set(CMAKE_CXX_STANDARD 17)

add_subdirectory(libs)
#<<<<<<< HEAD

include(FetchContent)
FetchContent_Declare(cpr GIT_REPOSITORY https://github.com/whoshuu/cpr.git GIT_TAG c8d33915dbd88ad6c92b258869b03aba06587ff9) # the commit hash for 1.5.0
FetchContent_MakeAvailable(cpr)

find_package(fmt REQUIRED)
find_package(restinio REQUIRED)

find_package(SFML 2.5 COMPONENTS graphics audio REQUIRED)

add_executable(main myMain.cpp)
target_link_libraries(main PUBLIC restinio::restinio fmt::fmt cpr::cpr presenter model response observer racer mechanicalValues sfml-graphics libserver libserialization libdata_struct libclient)
#=======
#find_package(SFML 2.5 COMPONENTS graphics REQUIRED)
#
#set(ALL_LIBS racer utils sfml-graphics response drawableObject drawableObjects drawableRacer viewer sfViewerDetails sfColor)
#
#add_executable(main main.cpp)
#target_link_libraries(main PUBLIC ${ALL_LIBS})
#
#
#enable_testing()
#find_package(GTest REQUIRED)
#include_directories(${GTEST_INCLUDE_DIRS} ${GTEST_LIBRARY} ${GTEST_INCLUDE_DIR} ${GTEST_MAIN_LIBRARY})
#
#add_executable(tests test.cpp)
#target_link_libraries(tests ${GTEST_LIBRARIES} -lpthread)
#target_link_libraries(tests ${ALL_LIBS})
#>>>>>>> view_kseny
