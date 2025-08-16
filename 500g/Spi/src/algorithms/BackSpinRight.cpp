#include "algorithms/BackSpinRight.hpp"

BackSpinRight::BackSpinRight(RobotAction *_robotAction) : Action(SPIN_DURATION + BACKUP_DURATION, 0, _robotAction) {
    robotAction = _robotAction;
    backup = new AutoTimer(BACKUP_DURATION);
    spin = new AutoTimer(SPIN_DURATION);
}

void BackSpinRight::performAction() {
    if (!backup->getReady()) { robotAction->back(255); }
    else if (!spin->getReady()) { robotAction->spinRight(255); }
}

void BackSpinRight::resetTimers() {
    backup->resetTimer();
    spin->resetTimer();
}