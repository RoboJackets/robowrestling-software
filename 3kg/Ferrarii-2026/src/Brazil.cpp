#include "Brazil.hpp"

Brazil::Brazil(WorldState* _worldState, RobotActions* _robotActions) {
    worldState = _worldState;
    robotActions = _robotActions;
    spinTimer = new Timer(SPIN_DURATION);
    backupTimer = new Timer(BACKUP_DURATION);
}

void Brazil::run() {
    SelfPositionEnum selfPosition = worldState->getOnLineStatus();
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
    SelfPositionEnum selfPosition = worldState->getOnLineStatus();
    if (resetTimers) {
        spinTimer->resetTimer();
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