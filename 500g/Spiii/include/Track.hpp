#ifndef TRACK
#define TRACK

#include "WorldState.hpp"
#include "RobotAction.hpp"
#include "Timer.hpp"

class Track {
    private:
        /* SPEEDS */
        const int MAX_SPEED = 255;
        const int SPEED = 100;
        const int FAST = 80;
        const int MOD = 60;
        const int SLOW = 40;

        /* TESTING SPEEDS */
        // const int MAX_SPEED = 100;
        // const int SPEED = 100;
        // const int FAST = 60;
        // const int MOD = 30;
        // const int SLOW = 10;

        const int BACKUP_DURATION = 100;
        Timer* backupTimer;

        WorldState* worldState;
        RobotAction* robotActions;
    public:
        Track(WorldState* _worldState, RobotAction* robotActions);
        void turnAccordingly(bool resetTimers);
        bool run();
};

#endif