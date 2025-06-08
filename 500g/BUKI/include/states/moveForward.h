#ifndef MOVE_FORWARD_H_
#define MOVE_FORWARD_H_

#include "states/robotState.h"
#include "action/robotAction.h"
#include "states/worldState.h"

class MoveForward : public RobotState {         // Polymorphism (I have no idea what's going on here - Shahmeel)
    private:
        RobotAction* robotAction;
    public:
        MoveForward(RobotAction* robotActionParameter);     // constructor
        void runAlgorithm() override;           // Override runAlgorithm() from RobotState
};

#endif