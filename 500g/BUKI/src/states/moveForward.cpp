#include "states/moveForward.h"

MoveForward::MoveForward(RobotAction* robotActionParameter) {       // constructor for MoveForward class. Takes a robotAction parameter (pointer to instance of robotAction in main) and assigns it to robotAction member variable
    robotAction = robotActionParameter;
}

void MoveForward::runAlgorithm() {      // calls runAlgorithm method of MoveForward class. Delegates movement of robot to robotAction object
    robotAction->go(0);                  // calls go() method on robotAction object
}