#ifndef TRACKER_H
#define TRACKER_H

#include "utility/Action.hpp"
#include "WorldState.h"
#include "BackSpin.hpp"
#include "Scan.hpp"

class Tracker {
    private:
        static constexpr int SLOW_SPEED = 60;
        static constexpr int MAX_SAFE_SPEED = 70;
        static constexpr int MODERATE_SPEED = 100;
        static constexpr int FAST_SPEED = 140;
        static constexpr int MAX_SPEED = 255;
        static constexpr int ACCELERATION_TIMER_DURATION = 4; //ms
        static constexpr int STUCK_TIMER_DURATION = 5000;
        static constexpr int BRAKE_TIMER_DURATION = 500;
        static constexpr int BACKUP_TIMER_DURATION = 500;
        int acceleration;
        int leftAcceleration;
        int rightAcceleration;
        bool stuck;
        Position previousPosition;
        AutoTimer *stuckTimer;
        AutoTimer *accelerationTimer;
        AutoTimer *brakeTimer;
        AutoTimer *backupTimer; // for getting unstuck
        BackSpin *backSpinLeft;
        BackSpin *backSpinRight;
        Scan *_scan;
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