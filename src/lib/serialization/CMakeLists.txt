add_library(libserialization SHARED serialization.cpp include/write.h write.cpp include/WriteJSONFunctor.h include/get_type_descriptor.h include/premetive.h)
target_include_directories(libserialization PUBLIC include)
target_link_libraries(libserialization libdata_struct)