add_library(startInfo STATIC src/menuInfo.cpp)

target_include_directories(startInfo PUBLIC include customRequest libcustomRequest gameClient buttons restiniofull libcustomDeserialization  libcustomRequest libstartServer libclient libdata_struct libserialization  cpr::cpr)
