#ifndef ALGORITHM_HPP
#include "Robot/robotActions.hpp"
#include "Sensors/irSensor.h"
#include "Sensors/lineSensor.h"
#include "Enumerations/OnLine.hpp"
#include "Enumerations/EnemyPositions.hpp"
#include "Sensors/Timer.hpp"

#define ALGORITHM_HPP

class Algorithm
{
private:
    RobotActions *action;

public:
    Algorithm(RobotActions *action, Timer *time);
    void RunItDown(EnemyPositions pos);
    void search();
    void backTrack(OnLine line_state);
};

#endif