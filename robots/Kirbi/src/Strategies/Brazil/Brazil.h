#ifndef BRAZIL_H
#define BRAZIL_H

#include <Arduino.h>
#include "Behaviors/Nodes/Node.h"
#include "Robots/RobotState.h"

class Brazil : public BT::Node<RobotState, RobotState> {
public:
    Brazil(int speed);

    RobotState Run(RobotState state);

private:
    int _speed;
};

#endif
