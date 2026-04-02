#include "Testing.hpp"

Testing::Testing(WorldState* _worldState, RobotActions* _robotActions) {
    worldState = _worldState;
    robotActions = _robotActions;
    stopflag = false;
}

void Testing::run() {
    SelfPositionEnum lineStatus = worldState->getOnLineStatus();
    if (stopflag) {
        robotActions->brake();
        return;
    }
    if (lineStatus == NOT_ON_LINE) {
        robotActions->forward(20);
    } else {
        stopflag = true;
        robotActions->brake();
    }
}