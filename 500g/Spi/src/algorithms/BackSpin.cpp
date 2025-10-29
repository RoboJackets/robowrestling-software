#include "algorithms/BackSpin.hpp"

BackSpin::BackSpin(RobotAction *_robotAction, bool _spinLeft) : Action(ACTION_DURATION, 0, _robotAction) {
    robotAction = _robotAction;
    spinLeft = _spinLeft;
    int spinDuration = spinLeft ? LEFT_SPIN_DURATION : RIGHT_SPIN_DURATION;
    int backTurnDuration = ACTION_DURATION - (spinDuration + BACKUP_DURATION);
    backup = new AutoTimer(BACKUP_DURATION);
    backTurn = new AutoTimer(backTurnDuration);
    spin = new AutoTimer(spinDuration);
}

void BackSpin::performAction() {
    if (!backTurn->getReady()) {
        if (spinLeft) { robotAction->turnBack(100, 255); }
        else { robotAction->turnBack(100, 255); }
    } else if (!backup->getReady()) {
        robotAction->back(255);
    } else if (!spin->getReady()) {
        robotAction->setSpeed(255);
        if (spinLeft) { robotAction->spinLeft(); }
        else { robotAction->spinRight(); }
    }
}

void BackSpin::resetTimers() {
    backup->resetTimer();
    spin->resetTimer();
    backTurn->resetTimer();
}