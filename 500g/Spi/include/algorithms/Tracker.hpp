#ifndef TRACKER_H
#define TRACKER_H

#include "utility/Action.hpp"
#include "WorldState.h"
#include "BackSpin.hpp"

class Tracker {
    private:
        static constexpr int SLOW_SPEED = 50;
        static constexpr int MAX_SAFE_SPEED = 70;
        static constexpr int FAST_SPEED = 140;
        static constexpr int MAX_SPEED = 255;
        static constexpr int ACCELERATION_TIMER_DURATION = 5; //ms
        int acceleration;
        AutoTimer *accelerationTimer;
        BackSpin *backSpinLeft;
        BackSpin *backSpinRight;
        Action *previousAction;
        RobotAction *robotAction;
        WorldState *worldState;
        void track();
        void seek();
        void scan();
    public:
        Tracker(WorldState *_worldState, RobotAction* _robotAction);
        void run();
};

#endif