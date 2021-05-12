add_library(libclient SHARED GameClient.cpp include/GameClient.hpp)
target_include_directories(libclient PUBLIC include)
target_link_libraries(libclient libdata_struct libserialization)
