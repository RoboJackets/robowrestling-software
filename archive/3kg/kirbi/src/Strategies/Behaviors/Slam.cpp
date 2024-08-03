#include "Strategies/Behaviors/Slam.h"

Slam::Slam(int speed) : BT::Node<RobotState, RobotState>(0, 0), speed(speed){}

RobotState Slam::Run(RobotState inputs) {
    this->_finished = inputs.lidars[2] > 150 || inputs.lidars[3] > 150; // neither lidars see anything

    RobotState out;
    out.currentLeftMotorPow  = speed;
    out.currentRightMotorPow = speed;
    return out;
}
