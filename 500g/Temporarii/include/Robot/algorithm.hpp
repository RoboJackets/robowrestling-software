#ifndef ALGORITHM_HPP
#include "Robot/robotActions.hpp"
#include "Sensors/IrSensor.hpp"
#include "Sensors/lineSensor.hpp"

#define ALGORITHM_HPP

class Algorithm
{
private:
    RobotActions *action;

public:
    Algorithm(RobotActions *action);
    void RunItDown();
    void search();
};

#endif