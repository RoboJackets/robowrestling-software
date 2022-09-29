add_library(Robots basicrobot.cpp newRobot.cpp)
target_include_directories(Robots PUBLIC ${CMAKE_CURRENT_SOURCE_DIR} PUBLIC ${CMAKE_SOURCE_DIR}/lib)
