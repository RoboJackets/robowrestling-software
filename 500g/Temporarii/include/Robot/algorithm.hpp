#include "Robot/robotActions.hpp"
#include "Sensors/IrSensor.hpp"
#include "Sensors/lineSensor.hpp"
#include "Enumerations/OnLine.hpp"
#include "Enumerations/EnemyPositions.hpp"
#include "Enumerations/AlgoLogs.hpp"
#include "Sensors/Timer.hpp"

#ifndef ALGORITHM_HPP
#define ALGORITHM_HPP

class Algorithm
{
private:
    RobotActions *action;
    Timer *timer;

public:
    Algorithm(RobotActions *action, Timer *timer);
    void RunItDown(EnemyPositions pos);
    void TurnToEnemy(EnemyPositions pos);
    void SideStrike(EnemyPositions pos);
    void search();
    void backTrack(OnLine line_state, AlgoLogs algo);
    void fryThem();
    bool getTimer();
};

#endif