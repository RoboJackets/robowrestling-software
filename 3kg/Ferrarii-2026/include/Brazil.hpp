#ifndef BRAZIL_H
#define BRAZIL_H

#include "WorldState.hpp"
#include "RobotActions.hpp"
#include "Timer.hpp"

class Brazil {
    private:
        const int SPEED = 210;
        const int BACKUP_DURATION = 40;
        const int SPIN_DURATION = 120 + BACKUP_DURATION;
        Timer* spinTimer;
        Timer* backupTimer;
        WorldState* worldState;
        RobotActions* robotActions;
    public:
        Brazil(WorldState* _worldState, RobotActions* robotActions);
        void run();
        void turnAccordingly(bool resetTimers);
};

#endif