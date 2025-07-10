// chooses an algorithm. class you call at the beginning to determine which algortihm to run

#include "states/robotState.h"

RobotState::RobotState() {
}

RobotState::RobotState(WorldState* worldStateParameter, StayOn* stayOnParameter, RobotAction* robotActionParameter) {
    worldState = worldStateParameter;
    stayOn = stayOnParameter;
    robotAction = robotActionParameter;
}

void RobotState::win() {
    // Decide which algorithm to run based on sensor data from WorldState class

    Edge enemy_pos = worldState->enemyPos();
    
    if (enemy_pos == SAFE) {
        stayOn->runAlgorithm();
    } else if (enemy_pos == CLOSE_FRONT) {
        robotAction->GOGOGO();
    } else if (enemy_pos == FRONT) {
        robotAction->go();
    } else if (enemy_pos == LEFT || enemy_pos == SLIGHT_LEFT) {
        robotAction->turnLeft();
    } else if (enemy_pos == SLIGHT_RIGHT) {
        robotAction->turnRight();
    } else {
        stayOn->runAlgorithm();
    }

}