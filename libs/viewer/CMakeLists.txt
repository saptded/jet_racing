add_library(viewer STATIC src/viewer.cpp)

target_include_directories(viewer PUBLIC include)
target_link_libraries(viewer PUBLIC response mechanicalValues sfViewerDetails)
