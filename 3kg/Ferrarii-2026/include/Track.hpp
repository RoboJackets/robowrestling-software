#ifndef TRACK
#define TRACK

#include "WorldState.hpp"
#include "RobotActions.hpp"
#include "Timer.hpp"

class Track {
    private:
        /* SPEEDS */
        const int MAX_SPEED = 255;
        const int SPEED = 210;
        const int FAST = 150;
        const int MOD = 100;
        const int SLOW = 80;

        /* TESTING SPEEDS */
        // const int MAX_SPEED = 100;
        // const int SPEED = 100;
        // const int FAST = 60;
        // const int MOD = 30;
        // const int SLOW = 10;


        const int BACKUP_DURATION = 40;
        Timer* backupTimer;

        WorldState* worldState;
        RobotActions* robotActions;
    public:
        Track(WorldState* _worldState, RobotActions* robotActions);
        void turnAccordingly(bool resetTimers);
        bool run();
};

#endif