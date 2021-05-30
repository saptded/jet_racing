add_library(gameTimer STATIC src/gameTimer.cpp)

target_include_directories(gameTimer PUBLIC include)
target_link_libraries(gameTimer PUBLIC sfml-graphics)
