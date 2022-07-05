
file(GLOB SRCS *.cpp) 
file(GLOB HDRS "include/*.h")
message("${HDRS}")
message("${PARENT_DIR}")
add_subdirectory(widgets)

