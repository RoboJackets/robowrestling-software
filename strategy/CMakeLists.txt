add_subdirectory(src)
add_library(Strategies src/slammywhammy.cpp src/basic_dist.cpp src/sensor_strategy.cpp src/roam_strategy.cpp src/avoid_strategy.cpp src/idle_strategy.cpp src/loop_strategy.cpp src/kevin_brody.cpp)
target_include_directories(Strategies PUBLIC ${CMAKE_CURRENT_SOURCE_DIR} PUBLIC ${CMAKE_SOURCE_DIR}/lib)
