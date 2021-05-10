add_library(drawableLine STATIC src/drawableLine.cpp)

target_include_directories(drawableLine PUBLIC include)
target_link_libraries(drawableLine PUBLIC utils drawableObject)
