#include "LockOn.hpp"

LockOn::LockOn(WorldState* _worldState, RobotAction* _robotAction) {
    worldState = _worldState;
    robotAction = _robotAction;
    complete = false;
    lockOnTimer = new Timer(LOCKON_TIMER_DURATION);
    previousActionTimer = new Timer(PREVIOUS_ACTION_DURATION);
}

bool LockOn::run() {
    if (complete) {
        return true;
    }
    OpponentPositionEnum enemyPosition = worldState->getEnemyPosition();
    if (enemyPosition == FRONT_CLOSE) {
        robotAction->brake();
    }
    else if (enemyPosition == REALLY_CLOSE_LEFT) {
        robotAction->brake();
    }
    else if (enemyPosition == REALLY_CLOSE_RIGHT) {
        robotAction->brake();
    }
    else if (enemyPosition == FRONT_FAR) {
        robotAction->brake();
    }
    else if (enemyPosition == MID_LEFT) {
        previousEnemyLocation = MID_LEFT;
        lockOnTimer->resetTimer();
        previousActionTimer->resetTimer();
        robotAction->spinLeft(SPEED);         
    }
    else if (enemyPosition == MID_RIGHT) {
        previousEnemyLocation = MID_RIGHT;
        lockOnTimer->resetTimer();
        previousActionTimer->resetTimer();
        robotAction->spinRight(SPEED);           
    }
    else if (enemyPosition == FAR_LEFT) {
        previousEnemyLocation = FAR_LEFT;
        lockOnTimer->resetTimer();
        previousActionTimer->resetTimer();
        robotAction->spinLeft(MAX_SPEED);
    }
    else if (enemyPosition == FAR_RIGHT) {
        previousEnemyLocation = FAR_RIGHT;
        lockOnTimer->resetTimer();
        previousActionTimer->resetTimer();
        robotAction->spinRight(MAX_SPEED);
    }
    else if (enemyPosition == NOT_SEEN) {
        lockOnTimer->resetTimer();
        if (!previousActionTimer->isReady()) {
            track();
        } else {
            complete = true;
        }
    }
    if (lockOnTimer->isReady()) {
        complete = true;
    }
    return complete;
}

void LockOn::track() {
    if (previousEnemyLocation == MID_LEFT) {
        robotAction->spinLeft(SPEED);         
    }
    else if (previousEnemyLocation == MID_RIGHT) {
        robotAction->spinRight(SPEED);           
    }
    else if (previousEnemyLocation == FAR_LEFT) {
        robotAction->spinLeft(MAX_SPEED);
    }
    else if (previousEnemyLocation == FAR_RIGHT) {
        robotAction->spinRight(MAX_SPEED);
    }
}