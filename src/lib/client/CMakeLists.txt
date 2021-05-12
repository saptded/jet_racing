add_library(libclient SHARED GameClient.cpp include/GameClient.hpp ../serialization/include/serialization.h)
target_include_directories(libclient PUBLIC include)
target_link_libraries(libclient libdata_struct libserialization)
