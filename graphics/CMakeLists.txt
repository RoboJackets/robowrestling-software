
file(GLOB SRCS *.cpp) 
file(GLOB HDRS "include/*.h")

add_library(graphics INTERFACE)
target_include_directories(graphics INTERFACE "include/") 
message("${HDRS}")
message("${PARENT_DIR}")
add_subdirectory(widgets)

