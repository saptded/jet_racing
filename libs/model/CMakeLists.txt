add_library(model STATIC src/model.cpp)

target_include_directories(model PUBLIC include)
target_link_libraries(model PUBLIC racer observer abstractModel racerController map startInfo restiniofull libcustomDeserialization  libcustomRequest libstartServer libclient libdata_struct libserialization  cpr::cpr)