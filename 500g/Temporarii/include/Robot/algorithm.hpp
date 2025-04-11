#ifndef ALGORITHM_HPP
#include "Robot/robotActions.hpp"
#include "Sensors/irSensor.h"
#include "Sensors/lineSensor.h"
#include "Enumerations/OnLine.hpp"

#define ALGORITHM_HPP

class Algorithm
{
private:
    RobotActions *action;

public:
    Algorithm(RobotActions *action);
    void RunItDown();
    void search();
    void backTrack(OnLine line_state);
};

#endif