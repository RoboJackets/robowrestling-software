#ifndef DASH
#define DASH

#include "WorldState.hpp"
#include "RobotActions.hpp"
#include "Timer.hpp"

class Dash {
    private:
        const int SPEED = 255;
        WorldState* worldState;
        RobotActions* robotActions;
        bool complete;
        bool started;
        Timer* dashTimer;
        const int DASH_DURATION = 160;
    public:
        Dash(WorldState* _worldState, RobotActions* robotActions);
        bool run();
};

#endif