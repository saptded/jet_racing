add_library(presenter STATIC src/presenter.cpp)

target_include_directories(presenter PUBLIC include)
target_link_libraries(presenter PUBLIC abstractModel observer model gameTimer)
