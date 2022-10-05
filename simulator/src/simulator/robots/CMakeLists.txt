add_library(Robots basicrobot.cpp AdvRobot.cpp)
target_include_directories(Robots PUBLIC ${CMAKE_CURRENT_SOURCE_DIR} PUBLIC ${CMAKE_SOURCE_DIR}/lib)
target_link_libraries(Robots LINK_PUBLIC graphics)
