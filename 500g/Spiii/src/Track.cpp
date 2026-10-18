#include "Track.hpp"

Track::Track(WorldState* _worldState, RobotAction* _robotActions) {
    worldState = _worldState;
    robotActions = _robotActions;
    backupTimer = new Timer(BACKUP_DURATION);
}

bool Track::run() {
    SelfPositionEnum selfPosition = worldState->getPosition();
    OpponentPositionEnum enemyPosition = worldState->getEnemyPosition();
    if (selfPosition != NOT_ON_LINE) {
        turnAccordingly(true);
        backupTimer->resetTimer();
        if (enemyPosition == NOT_SEEN) {
            return false;
        } else {
            return true;
        }
    } else if (!backupTimer->isReady()) {
        turnAccordingly(false);
        if (enemyPosition == NOT_SEEN) {
            return false;
        } else {
            return true;
        }
    }
    if (enemyPosition == NOT_SEEN) {
        return false;
    }
    if (enemyPosition == FRONT_CLOSE) {
        robotActions->forward(MAX_SPEED);
    }
    else if (enemyPosition == REALLY_CLOSE_LEFT) {
        robotActions->turn(FAST, MAX_SPEED);
    }
    else if (enemyPosition == REALLY_CLOSE_RIGHT) {
        robotActions->turn(MAX_SPEED, FAST);
    }
    else if (enemyPosition == FRONT_FAR) {
        robotActions->forward(MAX_SPEED);
    }
    else if (enemyPosition == MID_LEFT) {
        robotActions->turn(MOD, MAX_SPEED);         
    }
    else if (enemyPosition == MID_RIGHT) {
        robotActions->turn(MAX_SPEED, MOD);           
    }
    else if (enemyPosition == FAR_LEFT) {
        robotActions->spinLeft(MAX_SPEED);
    }
    else if (enemyPosition == FAR_RIGHT) {
        robotActions->spinRight(MAX_SPEED);
    }
    return true;
}

void Track::turnAccordingly(bool resetTimers) {
    SelfPositionEnum selfPosition = worldState->getPosition();
    if (resetTimers) {
        backupTimer->resetTimer();
    }
    if (selfPosition == ON_LINE_BOTTOM) {
        robotActions->forward(MAX_SPEED);
    }
    if (selfPosition == ON_LINE_LEFT) {
        robotActions->back(MAX_SPEED);
    }
    if (selfPosition == ON_LINE_RIGHT) {
        robotActions->back(MAX_SPEED);
    }
    if (selfPosition == ON_LINE_BOTH) {
        robotActions->back(MAX_SPEED);
    }
}