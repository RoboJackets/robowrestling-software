add_subdirectory(simulator/robots)
add_subdirectory(simulator/sensors)
add_executable(sim.sw simulator/sim.cpp simulator/physics/oldphysicsupdater.cpp simulator/physics/robotphysicsupdater.cpp simulator/physics/robotphysicsupdaterDEBUG.cpp)
target_link_libraries(sim.sw LINK_PUBLIC Robots Sensors Strategies Openings ${SFML_LIBRARIES} ${SFML_DEPENDENCIES})
