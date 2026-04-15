#include "Track.hpp"

Track::Track(WorldState* _worldState, RobotActions* _robotActions) {
    worldState = _worldState;
    robotActions = _robotActions;
    backupTimer = new Timer(BACKUP_DURATION);
}

bool Track::run() {
    SelfPositionEnum selfPosition = worldState->getOnLineStatus();
    OpponentPositionEnum enemyPosition = worldState->getOpponentPosition();
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
        robotActions->turnForward(FAST, SPEED);
    }
    else if (enemyPosition == REALLY_CLOSE_RIGHT) {
        robotActions->turnForward(MAX_SPEED, FAST);
    }
    else if (enemyPosition == FRONT_FAR) {
        robotActions->forward(SPEED);
    }
    else if (enemyPosition == CLOSE_LEFT) {
        robotActions->turnForward(MOD, SPEED);
    }
    else if (enemyPosition == CLOSE_RIGHT) {
        robotActions->turnForward(SPEED, MOD);
    }
    else if (enemyPosition == MID_LEFT) {
        robotActions->turnForward(SLOW, SPEED);            
    }
    else if (enemyPosition == MID_RIGHT) {
        robotActions->turnForward(SPEED, SLOW);            
    }
    else if (enemyPosition == FAR_LEFT) {
        robotActions->spinLeft(SPEED);
    }
    else if (enemyPosition == FAR_RIGHT) {
        robotActions->spinRight(SPEED);
    }
    else if (enemyPosition == BEHIND) {
        robotActions->spinLeft(SPEED);
    }
    return true;
}

void Track::turnAccordingly(bool resetTimers) {
    SelfPositionEnum selfPosition = worldState->getOnLineStatus();
    if (resetTimers) {
        backupTimer->resetTimer();
    }
    if (selfPosition == ON_LINE_BOTTOM_LEFT) {
        robotActions->forward(SPEED);
    }
    if (selfPosition == ON_LINE_BOTTOM_RIGHT) {
        robotActions->forward(SPEED);
    }
    if (selfPosition == ON_LINE_TOP_LEFT) {
        robotActions->backward(SPEED);
    }
    if (selfPosition == ON_LINE_TOP_RIGHT) {
        robotActions->backward(SPEED);
    }
}