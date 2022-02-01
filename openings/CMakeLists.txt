add_subdirectory(src)
add_library(Openings src/sample_opening.cpp)
target_include_directories(Openings PUBLIC ${CMAKE_CURRENT_SOURCE_DIR} PUBLIC ${CMAKE_SOURCE_DIR}/lib)
