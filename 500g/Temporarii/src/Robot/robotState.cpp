#include "Robot/robotState.hpp"
#include "Robot/algorithm.hpp"

// type | Class Name | function name
RobotState::RobotState(WorldState *state, Algorithm *algorithm) {
    worldState = state;
    this->algorithm = algorithm;
}
void RobotState::runAlgorithm() {
    // void State
    OnLine line_state = worldState->getIsOnLine();
    if (line_state != not_on_line) {
        algorithm->backTrack(line_state);
    } else if (worldState->getEnemyPosition() == SEND) {
        algorithm->RunItDown();
    } else {
        algorithm->search();
    }
}