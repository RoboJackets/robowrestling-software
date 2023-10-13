#ifndef ROBOT_STATE_H
#define ROBOT_STATE_H

#include "PhysicalState.h"

struct RobotState {
    PhysicalState pos_vel{};
    PhysicalState intent{};
    double currentLeftMotorPow = 0.0;
    double currentRightMotorPow = 0.0;
    bool atBounds = false;
    bool enabled = false;
};

#endif