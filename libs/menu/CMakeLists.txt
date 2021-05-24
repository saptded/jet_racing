add_library(menu STATIC src/menu.cpp)

target_include_directories(menu PUBLIC include)
target_link_libraries(menu PUBLIC presenter startInfo buttons restiniofull libstartServer  libclient libdata_struct libserialization  cpr::cpr)
