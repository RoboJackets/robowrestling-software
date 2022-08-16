enable_testing()
add_subdirectory(simulator/robots)
add_subdirectory(simulator/sensors)
add_subdirectory(simulator/tests)
add_executable(sim.sw simulator/sim.cpp simulator/physics/oldphysicsupdater.cpp simulator/physics/robotphysicsupdater.cpp)


add_executable(simtest simulator/tests/simtest.cpp simulator/physics/oldphysicsupdater.cpp simulator/physics/robotphysicsupdater.cpp) 
add_executable(phystest simulator/tests/physicstest.cpp simulator/physics/Vector2f.cpp simulator/physics/RigidBody2d.cpp)

target_include_directories(sim.sw PUBLIC ${OPENGL_INCLUDE_DIR})
target_link_libraries(sim.sw LINK_PUBLIC Robots Sensors Strategies Openings imgui widgets ${SFML_LIBRARIES} ${SFML_DEPENDENCIES} ${OPENGL_LIBRARIES})

target_link_libraries(simtest LINK_PUBLIC Robots Sensors Strategies Openings imgui widgets ${SFML_LIBRARIES} ${SFML_DEPENDENCIES} ${OPENGL_LIBRARIES})

target_link_libraries(simtest PUBLIC gtest_main)
target_link_libraries(phystest PUBLIC gtest_main gmock_main)
include(GoogleTest)

gtest_discover_tests(simtest)
gtest_discover_tests(phystest)
