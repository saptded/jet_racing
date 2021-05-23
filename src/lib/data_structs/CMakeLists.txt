add_library(libdata_struct SHARED  include include/2DPoint.h)
target_include_directories(libdata_struct PUBLIC include)
set_target_properties(libdata_struct PROPERTIES LINKER_LANGUAGE CXX)