#ifndef INCH
#define INCH

#include "WorldState.hpp"
#include "RobotActions.hpp"
#include "Timer.hpp"

class Inch {
    private:
        const int SPEED = 210;
        WorldState* worldState;
        RobotActions* robotActions;
        bool completed;
        bool started;

        Timer* inchTimer;
        Timer* brakeTimer;
        Timer* cutoffTimer;

        const int INCH_DURATION = 50;
        const int BRAKE_DURATION = 1000;
        const int CUTOFF_DURATION = 8000; 

    public:
        Inch(WorldState* _worldState, RobotActions* _robotActions);
        bool run();
};

#endif
