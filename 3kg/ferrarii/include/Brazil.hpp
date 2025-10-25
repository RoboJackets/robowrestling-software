#ifndef BRAZIL_H
#define BRAZIL_H

#include "WorldState.hpp"
#include "RobotActions.hpp"
#include "Speeds.hpp"
#include "Timer.hpp"

class Brazil {
    private:
        const int SPIN_DURATION = 250;
        Timer* spinTimer;
        WorldState* worldState;
        RobotActions* robotActions;
    public:
        Brazil(WorldState* _worldState, RobotActions* robotActions);
        void run();
        void turnAccordingly();
};

#endif