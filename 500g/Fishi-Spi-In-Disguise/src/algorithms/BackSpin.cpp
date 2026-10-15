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
    if (!backup->getReady()) {
        if (spinLeft) { robotAction->turnBack(100, 255); }
        else { robotAction->turnBack(100, 255); }
    }
    else if (!spin->getReady()) {
        robotAction->setSpeed(255);
        if (spinLeft) { robotAction->pivotLeft(); }
        else { robotAction->pivotRight(); }
    }
}

void BackSpin::resetTimers() {
    backup->resetTimer();
    spin->resetTimer();
}