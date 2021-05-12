add_library(racer STATIC src/racer.cpp)

target_include_directories(racer PUBLIC include)
#<<<<<<< HEAD
target_link_libraries(racer PUBLIC mechanicalValues racerController drawableRacer)
#=======
#target_link_libraries(racer PUBLIC utils drawableRacer)
#>>>>>>> view_kseny
