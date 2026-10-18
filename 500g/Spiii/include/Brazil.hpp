#ifndef BRAZIL_H
#define BRAZIL_H

#include "WorldState.hpp"
#include "RobotAction.hpp"
#include "Timer.hpp"

class Brazil {
    private:
        const int SPEED = 100;
        const int MAX_SPEED = 255;
        const int BACKUP_DURATION = 100;
        const int SPIN_DURATION = 120 + BACKUP_DURATION;
        Timer* spinTimer;
        Timer* backupTimer;
        WorldState* worldState;
        RobotAction* robotActions;
    public:
        Brazil(WorldState* _worldState, RobotAction* robotActions);
        void run();
        void turnAccordingly(bool resetTimers);
};

#endif