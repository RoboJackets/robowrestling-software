#include "states/stayOn.h"

StayOn::StayOn(RobotAction* robotActionParameter, WorldState* worldStateParameter) {       // constructor for MoveForward class. Takes a robotAction parameter (pointer to instance of robotAction in main) and assigns it to robotAction member variable
    robotAction = robotActionParameter;
    worldState = worldStateParameter;
    reverseTimer = 0;
}

void StayOn::runAlgorithm() {      // calls runAlgorithm method of MoveForward class. Delegates movement of robot to robotAction object
    Edge epos = worldState->isNearEdge(); 
    if (reverseTimer > 5) {
        robotAction->reverse();
        reverseTimer--;
    } else if (reverseTimer > 0) {
        robotAction->turnLeft();
        reverseTimer--;
    } else if (epos == FRONT) {
        robotAction->reverse();
        reverseTimer = 20;
    } else if (epos == LEFT || epos == SLIGHT_LEFT) {
        robotAction->turnRight();
    } else if (epos == RIGHT || epos == SLIGHT_RIGHT) {
        robotAction->turnLeft();
    } else {
        robotAction->go();
    }
}