#ifndef TRACKER_H
#define TRACKER_H

#include "utility/Action.hpp"
#include "WorldState.h"
#include "BackSpin.hpp"
#include "Scan.hpp"
#include "TurnAround.hpp"

class Tracker {
    private:
        static constexpr int SLOW_SPEED = 45;
        static constexpr int MAX_SAFE_SPEED = 70;
        static constexpr int MODERATE_SPEED = 100;
        static constexpr int FAST_SPEED = 140;
        static constexpr int MAX_SPEED = 255;
        static constexpr int ACCELERATION_TIMER_DURATION = 4; //ms
        static constexpr int STUCK_TIMER_DURATION = 8000;
        static constexpr int BRAKE_TIMER_DURATION = 500;
        static constexpr int BACKUP_TIMER_DURATION = 200;
        static constexpr int GO_TIMER = 200;
        static constexpr int STOP_TIMER = 30;
        static constexpr int TURN_TIMER_DURATION = 200;
        int acceleration;
        int leftAcceleration;
        int rightAcceleration;
        bool stuck;
        bool turnt;
        int mode;
        Position previousPosition;
        AutoTimer *stuckTimer;
        AutoTimer *accelerationTimer;
        AutoTimer *brakeTimer;
        AutoTimer *backupTimer; // for getting unstuck
        AutoTimer *stopTimer;
        AutoTimer *goTimer;
        AutoTimer *turnTimer;
        BackSpin *backSpinLeft;
        BackSpin *backSpinRight;
        Scan *_scan;
        TurnAround *turnAround;
        Action *previousAction;
        RobotAction *robotAction;
        WorldState *worldState;
        void track();
        void seek();
        void default_action();
    public:
        Tracker(WorldState *_worldState, RobotAction* _robotAction, int _mode);
        void run();
};

#endif