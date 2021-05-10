add_library(utils STATIC src/utils.cpp)

target_include_directories(utils PUBLIC include drawableObject)
target_link_libraries(utils PUBLIC drawableObject)