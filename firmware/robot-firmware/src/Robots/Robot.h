#ifndef ROBOT_H
#define ROBOT_H 

#include <Sensors/Sensor.h>
#include "Robots/RobotState.h"
#include <vector>

class Robot {
    protected: 
    std::vector<Sensor> _sensors; 
    RobotState _state; 

    public: 
    Robot() {}

    bool UpdateSensors() {}


    const RobotState& GetCurrentState() {
        return _state; 
    }



}; 


#endif 