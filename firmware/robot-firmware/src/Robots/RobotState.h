#ifndef ROBOT_STATE_H 
#define ROBOT_STATE_H

#include <array>
#include "util/Vector2.h"

struct RobotState {
    std::array<uint32_t, 6> lidars; 

    Vector2<double> position{0,0}; 
    Vector2<double> velocity{0,0}; 

    double theta = 0; 
    bool deployFlags = false; 
    double currentLeftMotorPow = 0.0; 
    double currentRightMotorPow = 0.0; 
    bool atBounds = false; 

    bool enabled = false; 

};


#endif 