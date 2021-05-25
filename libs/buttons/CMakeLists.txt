add_library(buttons STATIC src/buttons.cpp)

target_include_directories(buttons PUBLIC include)
target_link_libraries(buttons PUBLIC sfColor)
