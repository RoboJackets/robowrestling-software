#include "states/stayOn.h"

StayOn::StayOn(RobotAction* robotActionParameter, WorldState* worldStateParameter) {       // constructor for MoveForward class. Takes a robotAction parameter (pointer to instance of robotAction in main) and assigns it to robotAction member variable
    robotAction = robotActionParameter;
    worldState = worldStateParameter;
}

void StayOn::runAlgorithm() {      // calls runAlgorithm method of MoveForward class. Delegates movement of robot to robotAction object
    Edge epos = worldState->isNearEdge(); 
    if (epos == FRONT) {
        robotAction->reverse();
    } else if (epos == LEFT || epos == SLIGHT_LEFT) {
        robotAction->turnRight();
    } else if (epos == RIGHT || epos == SLIGHT_RIGHT) {
        robotAction->turnLeft();
    } else {
        robotAction->go();
    }
}