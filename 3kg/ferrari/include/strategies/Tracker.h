#ifndef SEARCH_H
#define SEARCH_H
#include "robot/RobotState.h"
#include "robot/WorldState.h"
class Tracker {
    private:
        int turnSpeed;
    public:
        Tracker(int turnSpeed);
        RobotState Run(RobotState inputs);
};
#endif