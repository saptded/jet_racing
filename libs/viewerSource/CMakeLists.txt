add_library(viewerSource STATIC src/viewerSource.cpp)

target_include_directories(viewerSource PUBLIC include)
target_link_libraries(viewerSource PUBLIC response utils viewerSourceRacer)
