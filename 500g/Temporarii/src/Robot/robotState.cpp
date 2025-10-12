#include "Robot/robotState.hpp"
#include "Robot/algorithm.hpp"

// Tempi's Home :)
RobotState::RobotState(WorldState *world, Algorithm *algo) {
    this->world = world;
    this->algo = algo;
}

// Selecting Algo 🌀🔄
void RobotState::runAlgorithm() {
    OnLine line_state = world->getIsOnLine();
    if (line_state != LineNone) {
        algo->backTrack(line_state);
    } else if (world->getEnemyPosition() == EnemyFront || world->getEnemyPosition() == EnemyFL || world->getEnemyPosition() == EnemyFR) {
        algo->RunItDown(world->getEnemyPosition());
    } else {
        algo->search();
    }
}