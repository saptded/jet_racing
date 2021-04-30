add_library(abstractModel STATIC src/abstractModel.cpp)

target_include_directories(abstractModel PUBLIC include)
target_link_libraries(abstractModel PUBLIC mechanicalValues observer)
