#ifndef MOVE_FORWARD_H_
#define MOVE_FORWARD_H_

#include "states/robotState.h"
#include "action/robotAction.h"
#include "states/worldState.h"

class MoveForward {
    private:
        RobotAction* robotAction;
    public:
        MoveForward(RobotAction* robotActionParameter);     // constructor
        void move();
};

#endif