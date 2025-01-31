#ifndef DEFENCE_H
#define DEFENCE_H

#include "robot/RobotActions.h"
#include "robot/WorldState.h"
#include "utility/Timer.hpp"



class Defence {
    private:
        int *currentTime;
        RobotActions *robotAction;
        WorldState *worldState;
        String state;
        Timer *lineTimer;

        void getOffTheDamnLine();
        void stare();
        void sendIt();
        void search();

        const int SLOW_SPEED = 30;
        const int MODERATE_SPEED = 80;
        const int MAX_SPEED = 127;
    public:
        Defence(int *currentTimePtr, RobotActions *robotAction, WorldState *worldState);
        void defend();
        String getState();
};

#endif