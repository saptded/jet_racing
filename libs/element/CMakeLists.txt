add_library(element STATIC src/Element.cpp)

target_include_directories(element PUBLIC include)

target_link_libraries(element PUBLIC math drawableObject drawableObjects racer racerController)

