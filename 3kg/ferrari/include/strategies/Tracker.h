#ifndef SEARCH_H
#define SEARCH_H

#include "robot/RobotActions.h"
#include "robot/WorldState.h"
class Tracker {
    private:
        int *currentTime;
    public:
        Tracker();
        void track();
};
#endif