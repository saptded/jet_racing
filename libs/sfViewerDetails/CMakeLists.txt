add_library(sfViewerDetails STATIC src/sfViewerDetails.cpp)

target_include_directories(sfViewerDetails PUBLIC include)
target_link_libraries(sfViewerDetails PUBLIC utils racer)
