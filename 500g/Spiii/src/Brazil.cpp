#include "Brazil.hpp"

Brazil::Brazil(WorldState* _worldState, RobotAction* _robotActions) {
    worldState = _worldState;
    robotActions = _robotActions;
    spinTimer = new Timer(SPIN_DURATION);
    backupTimer = new Timer(BACKUP_DURATION);
}

void Brazil::run() {
    SelfPositionEnum selfPosition = worldState->getPosition();
    if (selfPosition != NOT_ON_LINE) {
        turnAccordingly(true);
        spinTimer->resetTimer();
        backupTimer->resetTimer();
    } else if (!backupTimer->isReady()) {
        turnAccordingly(false);
    } else if (!spinTimer->isReady()) {
        robotActions->spinLeft(SPEED);
    } else {
        robotActions->forward(SPEED);
    }
}

void Brazil::turnAccordingly(bool resetTimers) {
    SelfPositionEnum selfPosition = worldState->getPosition();
    if (resetTimers) {
        spinTimer->resetTimer();
        backupTimer->resetTimer();
    }
    if (selfPosition == ON_LINE_LEFT) {
        robotActions->back(MAX_SPEED);
    }
    if (selfPosition == ON_LINE_RIGHT) {
        robotActions->back(MAX_SPEED);
    }
    if (selfPosition == ON_LINE_BOTTOM) {
        robotActions->forward(MAX_SPEED);
    }
    if (selfPosition == ON_LINE_BOTH) {
        robotActions->back(MAX_SPEED);
    }
}