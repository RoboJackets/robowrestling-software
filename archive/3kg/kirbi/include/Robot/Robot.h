#ifndef ROBOT_H
#define ROBOT_H

#include <Sensors/Sensor.h>
#include <vector>
#include <memory>
#include "Robot/RobotState.h"

class Robot {
protected:
    std::vector<Sensor*> _sensors;
    RobotState _state;

public:
    Robot() {}

    virtual void UpdateState() = 0;

    bool UpdateSensors();

    const RobotState& GetCurrentState();
};

#endif
