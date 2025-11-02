#include "Robot/robotState.hpp"
#include "Robot/algorithm.hpp"
#include "Enumerations/AlgoLogs.hpp"

// Tempi's Home :)
RobotState::RobotState(WorldState *world, Algorithm *algo) {
    this->world = world;
    this->algo = algo;
    this->prevAlgo = NoneAlgo;
}

// Selecting Algo 🌀🔄
void RobotState::runAlgorithm() {
    // Grab line_state for ease of use
    OnLine line_state = world->getIsOnLine();

    // Check queued algos first:
    if (algo->getTimer() == false) {
        prevAlgo == NoneAlgo;
    }

    // OVERRIDE: ALWAYS ATTACK IF ENEMY IS SEEN
    if (world->getEnemyPosition() == EnemyFront || world->getEnemyPosition() == EnemyFL || world->getEnemyPosition() == EnemyFR) {
        algo->RunItDown(world->getEnemyPosition());
        prevAlgo = RunItDown;
    }

    // Run queued algo
    if (prevAlgo == BTBackward) {
        algo->backTrack(line_state, prevAlgo);
        return;
    }

    // Basic check for lines and priority for algorithms
    if (line_state == LineFL || line_state == LineFR) {
        algo->backTrack(line_state, prevAlgo);
        prevAlgo = BTForward;
    } else if (line_state == LineBL || line_state == LineBR) {
        algo->backTrack(line_state, prevAlgo);
        prevAlgo = BTBackward;
    } else if (world->getEnemyPosition() == EnemyFront || world->getEnemyPosition() == EnemyFL || world->getEnemyPosition() == EnemyFR) {
        algo->RunItDown(world->getEnemyPosition());
        prevAlgo = RunItDown;
    } else {
        algo->search();
        prevAlgo = Search;
    }
}