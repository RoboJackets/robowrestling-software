#include "Robot/robotActions.hpp"
#include "Sensors/IrSensor.hpp"
#include "Sensors/lineSensor.hpp"
#include "Enumerations/OnLine.hpp"
#include "Enumerations/EnemyPositions.hpp"
#include "Enumerations/AlgoLogs.hpp"
#include "Sensors/Timer.hpp"
#include "Enumerations/SweepStates.hpp"

#ifndef ALGORITHM_HPP
#define ALGORITHM_HPP

class Algorithm
{
private:
    RobotActions *action;
    Timer *timer;
    bool line;
    float* yaw;

    SweepState sweepState;
    float theta_entry;
    float theta_exit;
    float theta_target;

public:
    Algorithm(RobotActions *action, Timer *timer, float *yaw_ptr);
    void Test();
    void RunItDown(EnemyPositions pos, AlgoLogs algo);
    void TurnToEnemy(EnemyPositions pos);
    void SideStrike(EnemyPositions pos);
    void search();
    void backTrack(OnLine line_state, AlgoLogs algo);
    void fryThem();
    void Strat2Sweep(bool midDetected);
    bool getTimer();
};

#endif