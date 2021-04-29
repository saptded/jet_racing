add_library(racer STATIC src/racer.cpp)

target_include_directories(racer PUBLIC include)
target_link_libraries(racer PUBLIC utils)
