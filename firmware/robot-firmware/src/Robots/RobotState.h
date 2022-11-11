#ifndef ROBOT_STATE_H 
#define ROBOT_STATE_H

#include <array>
#include "util/Vector2.h"

struct RobotState {
    std::array<int, 6> lidars; 

    Vector2<double> position{0,0}; 
    Vector2<double> velocity{0,0}; 

    double theta; 
    bool _deployFlags; 
    double currentLeftMotorPow; 
    double currentRightMotorPow; 

};


#endif 