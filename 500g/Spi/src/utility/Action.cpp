#include "utility/Action.hpp"

Action::Action(int _actionDuration, int _priority) {
    actionTimer = new AutoTimer(_actionDuration);
    priority = _priority;
    actionCompleted = false;
    actionInitiated = false;
}

bool Action::getActionCompleted() {
    if (actionTimer->getReady()) {
        actionCompleted = true;
    } else {
        actionCompleted = false;
    }
    return actionTimer->getReady(); 
}

void Action::run() {
    if (actionTimer->getReady()) {
        return;
    }
    if (actionCompleted) {
        return;
    }
    if (!actionInitiated) {
        actionTimer->resetTimer();
        actionInitiated = true;
    }
    performAction();
}

int Action::getPriority() {
    return priority;
}

void Action::resetAction() {
    actionInitiated = false;
    actionCompleted = false;
}