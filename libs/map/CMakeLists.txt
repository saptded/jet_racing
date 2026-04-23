add_library(map STATIC src/Map.cpp)

target_include_directories(map PUBLIC include)
target_link_libraries(map PUBLIC element parser)
