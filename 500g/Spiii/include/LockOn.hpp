#ifndef LOCKON_H
#define LOCKON_H

#include "WorldState.hpp"
#include "RobotAction.hpp"
#include "Timer.hpp"

class LockOn {
    private:
        WorldState *worldState;
        RobotAction *robotAction;
        const int SPEED = 70;
        const int MAX_SPEED = 255;
        const int LOCKON_TIMER_DURATION = 150;
        const int PREVIOUS_ACTION_DURATION = 500;
        bool complete;
        OpponentPositionEnum previousEnemyLocation;
        Timer *lockOnTimer;
        Timer *previousActionTimer;
        void track();
    public:
        LockOn(WorldState* _worldState, RobotAction* _robotAction);
        bool run();
};

#endif;