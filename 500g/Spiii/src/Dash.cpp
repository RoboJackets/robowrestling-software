#include "Dash.hpp"

Dash::Dash(WorldState* _worldState, RobotAction* _robotActions) {
    worldState = _worldState;
    robotActions = _robotActions;
    dashTimer = new Timer(DASH_DURATION);
    brakeTimer = new Timer(BRAKE_DURATION);
    complete = false;
    started = false;
}

bool Dash::run() {
    if (started == false) {
        started = true;
        dashTimer->resetTimer();
        brakeTimer->resetTimer();
    }
    if (!dashTimer->isReady()) {
        robotActions->forward(SPEED);
    } 
    else if (!brakeTimer->isReady()) {
        robotActions->brake();
    } else {
        complete = true;
    }
    return complete;
}