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
void RobotState::runAlgorithm(int strat_num) {
    // Grab line_state for ease of use
    OnLine line_state = world->getIsOnLine();

    // Decode strat (MODIFY for actual strategy name)
    Strategy strat = DefaultStrat;
    if (strat_num == 0) {
        strat = Strat1;
    } else if (strat_num == 1) {
        strat = Strat2;
    } else if (strat_num == 2) {
        strat = Strat3;
    } else if (strat_num == 3) {
        strat = Strat4;
    } else {
        strat = DefaultStrat;
    }

    // Check expiration
    if (algo->getTimer() == false) {
        prevAlgo = NoneAlgo;
    }

    algo->search();
    prevAlgo = Search;
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