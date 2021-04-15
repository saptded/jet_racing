cmake_minimum_required(VERSION 3.19)
project(for_project)

set(CMAKE_CXX_STANDARD 14)

find_package(SFML 2 REQUIRED graphics window)
include_directories(${SFML_INCLUDE_DIR})
include_directories ("include")

file(GLOB LIB_SOURCE_FILES
        ${PROJECT_SOURCE_DIR}/source/observer.cpp
        ${PROJECT_SOURCE_DIR}/source/view.cpp
        )
add_library( view STATIC ${LIB_SOURCE_FILES})

#add_executable(for_project main.cpp)
#target_link_libraries(for_project view)

enable_testing()
find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS} ${GTEST_LIBRARY} ${GTEST_INCLUDE_DIR} ${GTEST_MAIN_LIBRARY})

add_executable(tests tests.cpp)
target_link_libraries(tests ${GTEST_LIBRARIES} -lpthread)
target_link_libraries(tests view)

