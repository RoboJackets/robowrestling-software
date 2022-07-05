file(GLOB SRCS *.cpp)
add_library(imgui ${SRCS})
target_include_directories(imgui PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(imgui
  PUBLIC
    ${OPENGL_LIBRARIES}
)

