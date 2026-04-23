add_library(gameViewer STATIC src/gameViewer.cpp)

target_include_directories(gameViewer PUBLIC include)
target_link_libraries(gameViewer PUBLIC response mechanicalValues)
