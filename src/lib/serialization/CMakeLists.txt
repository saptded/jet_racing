add_library(libserialization SHARED serialization.cpp include/deserialization.h include/parser.h parser.cpp include/json_val.h)
target_include_directories(libserialization PUBLIC include)
target_link_libraries(libserialization libdata_struct)