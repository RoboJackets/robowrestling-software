#include "RobotState.h"

RobotState::RobotState(WorldState *worldStatePtr, RobotAction *robotActionPtr) {
    worldState = worldStatePtr;
    robotAction = robotActionPtr;
    actionTimer = new Timer();
    waitTimer = new Timer();
    backupTimer = new Timer();
    turnTimer = new Timer();
    startTimer = new Timer();
    startAction1Timer = new Timer();
    startTimer->setTimeInterval(500);
    startAction1Timer->setTimeInterval(75);
    backupTimer->setTimeInterval(100);
    turnTimer->setTimeInterval(100);
    actionTimer->setTimeInterval(750);
    waitTimer->setTimeInterval(250);
    backingUp = false;
}

void RobotState::calculateState(int time) {
    Position position = worldState->getPosition();
    Position enemyPosition = worldState->getEnemyPosition();
    if (position != Position::Off_Line) {
        backingUp = true;
        robotAction->setSpeed(255);
        robotAction->back();
        backupTimer->setPreviousTime(time);
        turnTimer->setPreviousTime(time);
    } else {
        if (backingUp) {
            if (!backupTimer->getReady() && !turnTimer->getReady()) {
                robotAction->setSpeed(80);
                robotAction->back();
            }
            if (backupTimer->getReady() && !turnTimer->getReady()) {
                robotAction->setSpeed(80);
                robotAction->spinLeft();
            }
            if (backupTimer->getReady() && turnTimer->getReady()) {
                backingUp = false;
            }
        }
        else if (enemyPosition != Position::None) {
            setAction(enemyPosition);
            waitTimer->setPreviousTime(time);
            actionTimer->setPreviousTime(time);
        }
        // disableing start sequence.
        // else if (!startTimer->getReady()) {
        //     robotAction->setSpeed(255);
        //     robotAction->forward();
        // }
        else if (enemyPosition == Position::None) {
            if (waitTimer->getReady() && !actionTimer->getReady()) { // if the wait is over and the action is not expired.
                robotAction->brake();
            }
            if (waitTimer->getReady() && actionTimer->getReady()) {
                waitTimer->setPreviousTime(time);
                actionTimer->setPreviousTime(time);
            }
            if (!waitTimer->getReady()) {
                robotAction->setSpeed(80);
                setAction(worldState->getLastEnemyPosition());
            }
        }
    }
    waitTimer->setCurrentTime(time);
    actionTimer->setCurrentTime(time);
    backupTimer->setCurrentTime(time);
    turnTimer->setCurrentTime(time);
    startAction1Timer->setCurrentTime(time);
    startTimer->setCurrentTime(time);
}

void RobotState::setAction(Position position) {
    if (position == Position::Middle_Close) {
        robotAction->setSpeed(255);
        robotAction->forward();
    }
    else if (position == Position::Middle_Far) {
        if (worldState->getEnemyPosition() != Position::None) {
            robotAction->setSpeed(180);
        } else {
            robotAction->setSpeed(80);
        }
        robotAction->forward();
    }
    else if (position == Position::Left) {
        robotAction->setSpeed(80);
        robotAction->pivotLeft();
    }
    else if (position == Position::Right) {
        robotAction->setSpeed(80);
        robotAction->pivotRight();
    }
}

void RobotState::setStartTimer(int time) {
    startTimer->setPreviousTime(time);
}