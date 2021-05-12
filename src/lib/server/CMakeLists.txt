add_library(libserver SHARED GameServer.cpp include/GameServer.hpp)
target_include_directories(libserver PUBLIC include)
target_link_libraries(libserver libdata_struct )
