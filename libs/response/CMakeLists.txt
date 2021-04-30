add_library(modelResponse STATIC src/response.cpp)

target_include_directories(modelResponse PUBLIC include)
target_link_libraries(modelResponse PUBLIC racer)