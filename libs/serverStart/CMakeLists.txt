add_library(libstartServer SHARED  src/startServer.cpp include/traits.h)
target_include_directories(libserver PUBLIC include)
target_link_libraries(libstartServer PUBLIC restiniofull libserver libclient libdata_struct libserialization)
