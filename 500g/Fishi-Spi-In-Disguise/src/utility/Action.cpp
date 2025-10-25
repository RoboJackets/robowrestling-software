#include "utility/Action.hpp"

Action::Action(int _actionDuration, int _priority, RobotAction *_robotAction) {
    if (_actionDuration == -1) {
        actionTimer = new AutoTimer(INT16_MAX);
    }
    actionTimer = new AutoTimer(_actionDuration);
    robotAction = _robotAction;
    priority = _priority;
    actionCompleted = true;
    actionInitiated = false;
}

bool Action::getActionCompleted() {
    if (!actionInitiated) {
        actionCompleted = true;
        return actionCompleted;
    }
    if (actionTimer->getReady()) {
        actionCompleted = true;
    } else {
        actionCompleted = false;
    }
    return actionCompleted; 
}

void Action::run() {
    if (!actionInitiated) {
        actionTimer->resetTimer();
        actionInitiated = true;
    }
    if (getActionCompleted()) {
        robotAction->brake();
    } else {
        performAction();
    }
}

int Action::getPriority() {
    return priority;
}

void Action::resetAction() {
    actionInitiated = false;
    actionCompleted = true;
    resetTimers();
}