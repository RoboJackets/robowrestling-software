#ifndef ROBOTSTATE_H
#define ROBOTSTATE_H

#include "WorldState.h"
#include "RobotActions.h"
#include "Timer.h"


class RobotState {
    private:
        WorldState *worldState;
        RobotActions *robotActions;
        MotorDriver *leftMotorDriver;
        MotorDriver *rightMotorDriver;
        Timer *turnTimer;
        Timer *backupTimer;
        bool backingUp;

    public:
        RobotState(WorldState *worldStatePtr, RobotActions *robotActionsPtr, MotorDriver *leftMotorDriverPointer, MotorDriver *rightMotorDriverPointer);
        void calculateState();
        void calculateState(int time);

};

#endif