#include "Robot/robotState.hpp"
#include "Robot/algorithm.hpp"
#include "Enumerations/AlgoLogs.hpp"

// Tempi's Home :)
RobotState::RobotState(WorldState *world, Algorithm *algo) {
    this->world = world;
    this->algo = algo;
    this->prevAlgo = NoneAlgo;
    this->enemyPrev = EnemyNone;
}

// Selecting Algo 🌀🔄
void RobotState::runAlgorithm() {
    // Grab line_state for ease of use
    OnLine line_state = world->getIsOnLine();

    // Check expiration
    if (algo->getTimer() == false) {
        prevAlgo = NoneAlgo;
    }

    algo->fryThem();
    prevAlgo = StirFry;
    return;

    // OVERRIDE: ALWAYS ATTACK IF ENEMY IS SEEN MID
    // if (world->getEnemyPosition() == EnemyFront) {
    //     algo->RunItDown(world->getEnemyPosition());
    //     prevAlgo = RunItDown;
    //     return;
    // }

    // // Enemy is in sights
    // if (world->getEnemyPosition() == EnemyFL || 
    //     world->getEnemyPosition() == EnemyFR || 
    //     world->getEnemyPosition() == EnemyLeft ||
    //     world->getEnemyPosition() == EnemyRight) {

    //     algo->TurnToEnemy(world->getEnemyPosition());
    //     enemyPrev = world->getEnemyPosition();
    //     prevAlgo = Turn;
    //     return;
    // }

    // Run remaining queued of Turn
    // if (prevAlgo == Turn) {
    //     algo->TurnToEnemy(enemyPrev);
    //     return;
    // }

    // Line Check First
    if (line_state == LineFL) {
        algo->backTrack(line_state, prevAlgo);
        prevAlgo = BTFL;
        return;
    } else if (line_state == LineFR) {
        algo->backTrack(line_state, prevAlgo);
        prevAlgo = BTFR;
        return;
    } else if (line_state == LineBL || line_state == LineBR) {
        algo->backTrack(line_state, prevAlgo);
        prevAlgo = BTBackward;
        return;
    }

    // Run queued algo
    if (prevAlgo == BTFR) {
        algo->backTrack(line_state, prevAlgo);
        prevAlgo = BTFR;
        return;
    } else if (prevAlgo == BTFL) {
        algo->backTrack(line_state, prevAlgo);
        prevAlgo = BTFL;
        return;
    } else if (prevAlgo == BTBackward) {
        algo->backTrack(line_state, prevAlgo);
        prevAlgo = BTBackward;
        return;
    } else if (prevAlgo == StirFry) {
        algo->fryThem();
        prevAlgo = StirFry;
        return;
    } else {
        // algo->search();
        // prevAlgo = Search;
        algo->fryThem();
        prevAlgo = StirFry;
        return;
    }
}