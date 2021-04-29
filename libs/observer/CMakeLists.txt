add_library(observer STATIC src/observer.cpp)

target_include_directories(observer PUBLIC include)
target_link_libraries(observer PUBLIC modelResponse)