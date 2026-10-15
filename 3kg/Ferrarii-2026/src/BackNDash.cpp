#include "BackNDash.hpp"

BackNDash::BackNDash(WorldState* _worldState, RobotActions* _robotActions) {
    worldState = _worldState;
    robotActions = _robotActions;
    hasHitBack = false;
    hasHitSide = false;
    complete = false;
    rightTurnTimer = new Timer(RIGHT_TURN_DURATION);
    runTimer = new Timer(RUN_DURATION);
    forwardTimer = new Timer(FORWARD_DURATION);
}

bool BackNDash::run() {
    if (complete == true) {
        return true;
    }
    SelfPositionEnum selfPosition = worldState->getOnLineStatus();
    if (hasHitBack == false) {
        robotActions->backward(SPEED);
        if (selfPosition != NOT_ON_LINE) {
            forwardTimer->resetTimer();
            hasHitBack = true;
        }
    } else if (!forwardTimer->isReady()) {
        if (selfPosition != NOT_ON_LINE) {
            forwardTimer->resetTimer();
        }
        robotActions->forward(SPEED);
        rightTurnTimer->resetTimer();
    } else if (!rightTurnTimer->isReady()) {
        robotActions->spinRight(SPEED);
        runTimer->resetTimer();
    } else if (!runTimer->isReady()) {
        robotActions->forward(SPEED);
    } else {
        complete = true;
    }
    return complete;
}