#ifndef ROBOT_H
#define ROBOT_H

#include <vector>
#include <memory>
#include "RobotState.h"
#include "sensors/Sensor.h"

class Robot {

protected:
    std::vector<Sensor*> _sensors;
    RobotState _state;

public:
    Robot() {}

    virtual void updateState() = 0;

    bool updateSensors() {
        for (Sensor* sensor : _sensors) {
            sensor->Poll();
        }
        updateState();
        return true;
    }

    RobotState& getState() {
        return _state;
    }

};

#endif