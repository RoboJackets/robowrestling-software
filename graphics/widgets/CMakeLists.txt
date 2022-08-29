

file(GLOB SRCS "*.cpp") 



message(${SRCS})
add_library(widgets ${SRCS}) 
include_directories(widgets PUBLIC)
target_include_directories(widgets PUBLIC "${PROJECT_SOURCE_DIR}/graphics/include/")
target_link_libraries(widgets PUBLIC imgui) 
