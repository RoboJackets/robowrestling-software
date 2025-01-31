#ifndef MOVE_FORWARD_H_
#define MOVE_FORWARD_H_

#include "states/robotState.h"

class MoveForward : public RobotState {         // Polymorphism -> GeeksforGeeks
    public:
        MoveForward();
        void runAlgorithm() override;
};

#endif