#ifndef MOVE_FORWARD_H_
#define MOVE_FORWARD_H_

#include "states/robotState.h"

class MoveForward : public RobotState {
    public:
        MoveForward();
        void runAlgorithm() override;
};

#endif