add_library(drawableObjects STATIC src/drawableObjects.cpp)

target_include_directories(drawableObjects PUBLIC include)
target_link_libraries(drawableObjects PUBLIC utils drawableObject sfColor)
