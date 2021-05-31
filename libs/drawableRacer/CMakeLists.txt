add_library(drawableRacer STATIC src/drawableRacer.cpp)

target_include_directories(drawableRacer PUBLIC include)
target_link_libraries(drawableRacer PUBLIC response mechanicalValues racer sfColor)
