add_subdirectory(simulator/robots)
add_subdirectory(simulator/sensors)
add_executable(sim.sw simulator/sim.cpp simulator/physics/testphysicsupdater.cpp simulator/physics/robotphysicsupdater.cpp)
target_link_libraries(sim.sw LINK_PUBLIC Robots Sensors Strategies ${SFML_LIBRARIES} ${SFML_DEPENDENCIES})
