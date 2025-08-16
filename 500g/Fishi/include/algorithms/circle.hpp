#ifndef CIRCLE_H
#define CIRCLE_H

#include "utility/AutoTimer.hpp"
#include "RobotAction.h"
#include "WorldState.h"
#include "Arduino.h"

class Circle {
    private:
        WorldState *worldState;
        RobotAction *robotAction;
        bool hasDoneStartSequence;
        AutoTimer *turn90;
        AutoTimer *whiteAdjust;
        AutoTimer *blackAdjust;
        int rightSpeed;
        int leftSpeed;
        bool wasBlack;
        bool wasWhite;
    public:
        Circle(WorldState *_worldState, RobotAction *_robotAction);
        void run();
};

#endif 