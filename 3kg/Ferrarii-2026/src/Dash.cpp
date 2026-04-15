#include "Dash.hpp"

Dash::Dash(WorldState* _worldState, RobotActions* _robotActions) {
    worldState = _worldState;
    robotActions = _robotActions;
    dashTimer = new Timer(DASH_DURATION);
    complete = false;
    started = false;
}

bool Dash::run() {
    if (started == false) {
        started = true;
        dashTimer->resetTimer();
    }
    if (!dashTimer->isReady()) {
        robotActions->forward(SPEED);
    } else {
        complete = true;
    }
    return complete;
}