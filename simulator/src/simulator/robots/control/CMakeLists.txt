file(GLOB SRCS *.cpp) 

add_library(Control ${SRCS})
target_include_directories(Contorl PUBLIC ${CMAKE_CURRENT_SOURCE_DIR} PUBLIC ${CMAKE_SOURCE_DIR}/lib)