#ifndef INCHFORWARD_H
#define INCHFORWARD_H

#include "utility/AutoTimer.hpp"
#include "WorldState.h"
#include "RobotAction.h"
#include "enumerations/PositionEnum.h" 

class InchForward {
    private:
        int speed;
        AutoTimer *moving;
        AutoTimer *stopped;
        WorldState *worldState;
        RobotAction *robotAction;
    public:
        InchForward(WorldState *_worldState, RobotAction *_robotAction, int _speed);
        void inch();
        void moveInEnemyDirection();
};

#endif