#include "states/dodge.h"

Dodge::Dodge(RobotAction* robotActionParameter, WorldState* worldStateParameter) {
    robotAction = robotActionParameter;
    worldState = worldStateParameter;
}

void Dodge::performDodge() {
    // implement logic to decide how long to turn and GOGOGO
    robotAction->turnRight();
    robotAction->GOGOGO();
}

