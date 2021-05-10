add_library(parser STATIC src/Parser.cpp)

target_include_directories(parser PUBLIC include)
target_link_libraries(parser PUBLIC element)