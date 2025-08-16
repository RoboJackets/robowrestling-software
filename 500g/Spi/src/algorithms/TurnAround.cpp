#include "algorithms/TurnAround.hpp"

TurnAround::TurnAround(WorldState *_worldState, RobotAction *_robotAction) {
    worldState = _worldState;
    robotAction = _robotAction;
    leftTimer = new AutoTimer(leftTimerLength);
    rightTimer = new AutoTimer(rightTimerLength);
}

void TurnAround::TurnAroundLeft() {
    robotAction->setSpeed(255);
    robotAction->spinLeft();
}

void TurnAround::TurnAroundRight() {
    robotAction->setSpeed(255);
    robotAction->spinRight();
}