cmake_minimum_required(VERSION 3.13)
project(jet_racing)
set(CMAKE_CXX_STANDARD 17)

add_subdirectory(libs)
#<<<<<<< HEAD

find_package(SFML 2.5 COMPONENTS graphics audio REQUIRED)

add_executable(main myMain.cpp)
target_link_libraries(main PUBLIC presenter model modelResponse observer racer mechanicalValues sfml-graphics)
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
