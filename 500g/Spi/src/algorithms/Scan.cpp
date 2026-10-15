#include "algorithms/Scan.hpp"

Scan::Scan(RobotAction *_robotAction) : Action(ACTION_DURATION, 0, _robotAction) {
    robotAction = _robotAction;
}

void Scan::performAction() {
    robotAction->spinLeft(SLOW_SPEED);
}

void Scan::resetTimers() {

}