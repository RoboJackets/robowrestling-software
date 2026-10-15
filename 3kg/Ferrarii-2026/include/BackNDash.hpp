#ifndef BACKNDASH
#define BACKNDASH

#include "WorldState.hpp"
#include "RobotActions.hpp"
#include "Timer.hpp"

class BackNDash {
    private:
        const int SPEED = 210;
        WorldState* worldState;
        RobotActions* robotActions;

        /* flags */
        bool hasHitBack;
        bool hasHitSide;
        bool complete;

        /* timers */
        Timer* rightTurnTimer;
        Timer* runTimer;
        Timer* forwardTimer;

        const int RIGHT_TURN_DURATION = 35;
        const int RUN_DURATION = 150;
        const int FORWARD_DURATION = 20;

    public:
        BackNDash(WorldState* _worldState, RobotActions* robotActions);
        bool run();
};

#endif