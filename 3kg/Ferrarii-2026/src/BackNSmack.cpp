#include "BackNSmack.hpp"

BackNSmack::BackNSmack(WorldState* _worldState, RobotActions* _robotActions) {
    worldState = _worldState;
    robotActions = _robotActions;
    hasHitBack = false;
    hasHitSide = false;
    complete = false;
    rightTurnTimer = new Timer(RIGHT_TURN_DURATION);
    leftTurnTimer = new Timer(LEFT_TURN_DURATION);
    runTimer = new Timer(RUN_DURATION);
    forwardTimer = new Timer(FORWARD_DURATION);
    backTimer = new Timer(BACK_DURATION);
}

bool BackNSmack::run() {
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
    } else if (hasHitSide == false) {
        robotActions->forward(SPEED);
            if (selfPosition != NOT_ON_LINE) {
                backTimer->resetTimer();
                hasHitSide = true;
            }
    } else if (!backTimer->isReady()) {
        if (selfPosition != NOT_ON_LINE) {
            backTimer->resetTimer();
        }
        robotActions->backward(SPEED);
        leftTurnTimer->resetTimer();
    } else if (!leftTurnTimer->isReady()) {
        robotActions->spinLeft(SPEED);
        runTimer->resetTimer();
    } else if (!runTimer->isReady()) {
        robotActions->forward(SPEED);
    } else {
        complete = true;
    }
    return complete;
}