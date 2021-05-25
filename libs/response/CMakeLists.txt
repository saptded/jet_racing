#<<<<<<< HEAD
add_library(response STATIC src/response.cpp)

target_include_directories(response PUBLIC include)
target_link_libraries(response PUBLIC racer element)
#=======
#add_library(response STATIC src/response.cpp)
#
#target_include_directories(response PUBLIC include)
#target_link_libraries(response PUBLIC utils racer)
#>>>>>>> view_kseny
