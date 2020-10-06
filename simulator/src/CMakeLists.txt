








add_executable(sim simulator/sim.cpp simulator/basicrobot.cpp)
target_link_libraries(sim ${SFML_LIBRARIES} ${SFML_DEPENDENCIES})
