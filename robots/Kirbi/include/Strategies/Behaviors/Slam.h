#ifndef SLAM_H
#define SLAM_H

#include "Robot/RobotState.h"
#include "Strategies/Behaviors/Nodes/Node.h"

class Slam : public BT::Node<RobotState, RobotState> {
public:
    Slam(int speed);

    RobotState Run(RobotState inputs) override;

protected:
    int speed;
};

#endif
