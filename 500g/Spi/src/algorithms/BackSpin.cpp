#include "algorithms/BackSpin.hpp"

BackSpin::BackSpin(RobotAction *_robotAction, bool _spinLeft) : Action(ACTION_DURATION, 0, _robotAction) {
    robotAction = _robotAction;
    spinLeft = _spinLeft;
    int spinDuration = spinLeft ? LEFT_SPIN_DURATION : RIGHT_SPIN_DURATION;
    int backupDuration = ACTION_DURATION - spinDuration;
    backup = new AutoTimer(backupDuration);
    spin = new AutoTimer(spinDuration);
}

void BackSpin::performAction() {
    if (!backup->getReady()) { robotAction->back(255); }
    else if (!spin->getReady()){
        if (spinLeft) { robotAction->spinLeft(255); }
        else { robotAction->spinRight(255); }
    }
}

void BackSpin::resetTimers() {
    backup->resetTimer();
    spin->resetTimer();
}