add_library(sfGameViewer STATIC src/sfGameViewer.cpp)

target_include_directories(sfGameViewer PUBLIC include)
target_link_libraries(sfGameViewer PUBLIC gameViewer response sfViewerDetails)
