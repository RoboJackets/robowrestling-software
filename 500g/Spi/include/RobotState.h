#ifndef ROBOTSTATE_H
#define ROBOTSTATE_H

#include "WorldState.h"
#include "RobotAction.h"
#include "Timer.h"

class RobotState {
    private:
        WorldState *worldState;
        RobotAction *robotAction;
        Timer *actionTimer;
        Timer *waitTimer;
        Timer *backupTimer;
        Timer *turnTimer;
        Timer *startTimer;
        Timer *startAction1Timer;
        bool backingUp;
        void setAction(Position position);
    public:
        RobotState(WorldState *worldStatePtr, RobotAction *robotActionPtr);
        void setStartTimer(int time);
        void calculateState(int time);
};

#endif