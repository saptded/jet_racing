add_library(logger STATIC src/Logger.cpp)

add_definitions(-DBOOST_LOG_DYN_LINK)
find_package(Boost COMPONENTS log_setup log REQUIRED)
include_directories(${Boost_INCLUDE_DIRS})

target_include_directories(logger PUBLIC include)
target_link_libraries(logger PUBLIC ${Boost_LIBRARIES})
