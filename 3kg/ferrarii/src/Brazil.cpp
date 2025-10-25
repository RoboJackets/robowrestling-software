#include "Brazil.hpp"

Brazil::Brazil(WorldState* _worldState, RobotActions* _robotActions) {
    worldState = _worldState;
    robotActions = _robotActions;
    spinTimer = new Timer(SPIN_DURATION);
}

void Brazil::run() {
    SelfPositionEnum selfPosition = worldState->getOnLineStatus();
    if (selfPosition != NOT_ON_LINE) {
        turnAccordingly();
    } else if (!spinTimer->isReady()) {
        robotActions->spinLeft(MAX_SPEED);
    } else {
        robotActions->forward(SAFE_SPEED);
    }
}

void Brazil::turnAccordingly() {
    SelfPositionEnum selfPosition = worldState->getOnLineStatus();
    spinTimer->resetTimer();
    if (selfPosition == ON_LINE_BOTTOM_LEFT) {
        robotActions->forward(FAST_SPEED);
    }
    if (selfPosition == ON_LINE_BOTTOM_RIGHT) {
        robotActions->forward(FAST_SPEED);
    }
    if (selfPosition == ON_LINE_TOP_LEFT) {
        robotActions->backward(MAX_SPEED);
    }
    if (selfPosition == ON_LINE_TOP_RIGHT) {
        robotActions->backward(MAX_SPEED);
    }
}