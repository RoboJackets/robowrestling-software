add_subdirectory(src)
add_library(Strategies src/slammywhammy.cpp src/basic_dist.cpp)
target_include_directories(Strategies PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})