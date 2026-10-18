#ifndef INCH
#define INCH

#include "WorldState.hpp"
#include "RobotAction.hpp"
#include "Timer.hpp"

class Inch {
    private:
        const int SPEED = 210;
        WorldState* worldState;
        RobotAction* robotAction;
        bool completed;
        bool started;

        Timer* inchTimer;
        Timer* brakeTimer;
        Timer* cutoffTimer;

        const int INCH_DURATION = 80;
        const int BRAKE_DURATION = 1000;
        const int CUTOFF_DURATION = 8000; 

    public:
        Inch(WorldState* _worldState, RobotAction* _robotAction);
        bool run();
};

#endif
