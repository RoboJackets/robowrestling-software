#include "algorithms/BackSpinLeft.hpp"

BackSpinLeft::BackSpinLeft(RobotAction *_robotAction) : Action(SPIN_DURATION + BACKUP_DURATION, 0, _robotAction) {
    robotAction = _robotAction;
    backup = new AutoTimer(BACKUP_DURATION);
    spin = new AutoTimer(SPIN_DURATION);
}

void BackSpinLeft::performAction() {
    if (!backup->getReady()) { robotAction->back(255); }
    else if (!spin->getReady()) { robotAction->spinLeft(255); }
}