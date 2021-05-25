add_library(drawableObject STATIC src/drawableObject.cpp)

target_include_directories(drawableObject PUBLIC include)
target_link_libraries(drawableObject PUBLIC element)
