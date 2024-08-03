#ifndef FULLREVERSE_H
#define FULLREVERSE_H

#include <Arduino.h>
#include "Robot/RobotState.h"
#include "Strategies/Behaviors/Nodes/Node.h"

class FullReverse : public BT::Node<RobotState, RobotState> {
public:
    FullReverse(int speed);

    RobotState Run(RobotState inputs) override;

protected:
    int speed;
};

#endif
