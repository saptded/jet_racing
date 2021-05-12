#<<<<<<< HEAD
add_library(modelResponse STATIC src/response.cpp)

target_include_directories(modelResponse PUBLIC include)
target_link_libraries(modelResponse PUBLIC racer)
#=======
#add_library(response STATIC src/response.cpp)
#
#target_include_directories(response PUBLIC include)
#target_link_libraries(response PUBLIC utils racer)
#>>>>>>> view_kseny
