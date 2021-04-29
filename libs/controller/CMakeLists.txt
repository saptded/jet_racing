add_library(controller STATIC src/controller.cpp)

target_include_directories(controller PUBLIC include)
target_link_libraries(controller PUBLIC model)