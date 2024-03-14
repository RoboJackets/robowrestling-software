#include "Strategies/Behaviors/FullReverse.h"

FullReverse::FullReverse(int speed) : BT::Node<RobotState, RobotState>(0, 0), speed(speed) {}

RobotState FullReverse::Run(RobotState inputs) {
    RobotState out;
    out.currentLeftMotorPow  = -speed;
    out.currentRightMotorPow = -speed;
    return out;
}
