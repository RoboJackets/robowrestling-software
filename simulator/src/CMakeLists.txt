








add_executable(sim.sw simulator/sim.cpp simulator/basicrobot.cpp simulator/physics/robotphysicsupdater.cpp simulator/sensors/distance_sensor.cpp)
target_link_libraries(sim.sw ${SFML_LIBRARIES} ${SFML_DEPENDENCIES})
