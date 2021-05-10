add_library(drawableArc STATIC src/drawableArc.cpp)

target_include_directories(drawableArc PUBLIC include)
target_link_libraries(drawableArc PUBLIC utils drawableObject)
