// chooses an algorithm. class you call at the beginning to determine which algortihm to run

#include "states/robotState.h"

RobotState::RobotState(WorldState* worldStateParameter) : worldState(worldStateParameter) {}

void RobotState::runAlgorithm() {
    // Decide which algorithm to run based on sensor data from WorldState class
}