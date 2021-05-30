add_library(model STATIC src/model.cpp)

target_include_directories(model PUBLIC include)
target_link_libraries(model PUBLIC racer observer abstractModel racerController)
