#ifndef DASH_H
#define DASH_H

#include "WorldState.hpp"
#include "RobotAction.hpp"
#include "Timer.hpp"

class Dash {
    private:
        const int SPEED = 255;
        WorldState* worldState;
        RobotAction* robotActions;
        bool complete;
        bool started;
        Timer* dashTimer;
        Timer* brakeTimer;
        const int DASH_DURATION = 280;
        const int BRAKE_DURATION = 30 + DASH_DURATION;
    public:
        Dash(WorldState* _worldState, RobotAction* _robotAction);
        bool run();
};

#endif