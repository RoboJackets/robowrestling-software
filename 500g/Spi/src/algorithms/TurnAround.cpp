#include "algorithms/TurnAround.hpp"

TurnAround::TurnAround(RobotAction *_robotAction) : Action(ACTION_DURATION, 0, _robotAction) {
    robotAction = _robotAction;
}

void TurnAround::performAction() {
    robotAction->spinLeft(SPEED);
}

void TurnAround::resetTimers() {

}