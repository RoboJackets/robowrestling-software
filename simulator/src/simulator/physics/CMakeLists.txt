file(GLOB SRCS *.cpp)

add_library(Physics ${SRCS} )

target_include_directories(Physics PUBLIC ${CMAKE_CURRENT_SOURCE_DIR} PUBLIC ${CMAKE_SOURCE_DIR}/lib)
