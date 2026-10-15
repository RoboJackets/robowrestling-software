#ifndef BACKNSMACK
#define BACKNSMACK

#include "WorldState.hpp"
#include "RobotActions.hpp"
#include "Timer.hpp"

class BackNSmack {
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
        Timer* leftTurnTimer;
        Timer* runTimer;
        Timer* forwardTimer;
        Timer* backTimer;

        const int RIGHT_TURN_DURATION = 40;
        const int LEFT_TURN_DURATION = 30;
        const int RUN_DURATION = 250;
        const int FORWARD_DURATION = 20;
        const int BACK_DURATION = 20;

    public:
        BackNSmack(WorldState* _worldState, RobotActions* robotActions);
        bool run();
};

#endif