#ifndef ROBOT_STATE_H
#define ROBOT_STATE_H

#include "PhysicalState.h"
#include "DistanceToEnemy.h"

struct RobotState {
    PhysicalState pos_vel{};
    PhysicalState intent{};
    double currentLeftMotorPow = 0.0;
    double currentRightMotorPow = 0.0;
    bool atBounds = false;
    bool enabled = false;

    //x is left sensor, y is right sensor
    Vector2<uint32_t> distanceToEnemy{};
    DistanceToEnemy distanceToEnemy{};
};

#endif