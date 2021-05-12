add_library(parser STATIC src/Parser.cpp)

find_package(Boost REQUIRED)
include_directories(${Boost_INCLUDE_DIRS})

target_include_directories(parser PUBLIC include)
target_link_libraries(parser PUBLIC element ${Boost_LIBRARIES})
