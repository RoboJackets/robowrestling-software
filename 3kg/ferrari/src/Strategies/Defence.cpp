#include "strategies/Defence.hpp"

Defence::Defence(int *currentTimePtr, RobotActions *robotActionPtr, WorldState *worldStatePtr) {
    currentTime = currentTimePtr;
    robotAction = robotActionPtr;
    worldState = worldStatePtr;
    lineTimer = new Timer(500, currentTimePtr);
}

void Defence::defend() {
    // priority 1, back up from line
    if (worldState->getIsOnLine() != NOT_ON_LINE) {
        getOffTheDamnLine();
    }
    // priority 2, we are fresh off line, maybe need to spin or something?
    else if (!lineTimer->getReady()) {
        robotAction->spinLeft(); // this is max speed
    }
    // priority 3, if opponent is on plow or close center, kill em.
    else if (worldState->getEnemyPosition() == OP_CLOSE_CENTER || worldState->getEnemyPosition() == OP_ON_PLOW) {
        sendIt();
    }
    // priority 4, look at opponent (spin in place)
    else if (worldState->getEnemyPosition() != OP_NOT_FOUND) {
        stare();
    }
    // priority 5, take the L (probably)
    else if (worldState->getEnemyPosition() == OP_NOT_FOUND) {
        search();
    // priority 6, brake, ideally they are far center
    } else {
        robotAction->brake();
    }
}

String Defence::getState() {
    return state;
}

void Defence::getOffTheDamnLine() {
    state = "getting off line";
    if (worldState->getIsOnLine() == ON_LINE_BOTTOM_LEFT || worldState->getIsOnLine() == ON_LINE_BOTTOM_RIGHT) {
        robotAction->driveForward(MODERATE_SPEED);
    }
    else {
        lineTimer->setStartTime(*currentTime);
        robotAction->driveBackward(MODERATE_SPEED);
    }
}

void Defence::sendIt() {
    state = "sending it";
    robotAction->driveForward(); // <3
}

void Defence::stare() {
    state = "staring";
    if (worldState->getEnemyPosition() == OP_LEFT_30 || worldState->getEnemyPosition() == OP_LEFT_90) {
        robotAction->spinLeft(MODERATE_SPEED); // max speed
    }
    else {
        robotAction->spinRight(MODERATE_SPEED);
    }
}

void Defence::search() {
    state = "searching";
    if (worldState->getEnemyPosition() == OP_NOT_FOUND) {
        robotAction->driveForward(SLOW_SPEED);
    }
    else if (worldState->getLastEnemyPosition() == OP_LEFT_30 || worldState->getLastEnemyPosition() == OP_LEFT_90) {
        robotAction->spinLeft(MODERATE_SPEED);
    }
    else {
        robotAction->spinRight(MODERATE_SPEED);
    }
}