#ifndef ROBOT_H
#define ROBOT_H 

#include <Sensors/Sensor.h>
#include <vector>

class Robot {
    protected: 
    float _x; 
    float _y; 
    std::vector<Sensor> _sensors; 

    public: 
    Robot() : _x(0), _y(0) {}

    bool UpdateSensors() {}


}; 


#endif 