#ifndef STRAT_H
#define STRAT_H

#include "WorldState.hpp"
#include "RobotActions.hpp"
#include "Speeds.hpp"
#include "Timer.hpp"

class Strat {
    private:
        WorldState* worldState;
        RobotActions* robotActions;

        const int NOT_SEEN_TIMER_DURATION = 1000;
        const int BACKUP_TIMER_DURATION = 200;
        const int SPIN_TIMER_DURATION = BACKUP_TIMER_DURATION + 200;
        const int INCH_TIMER_DURATION = 300;
        const int STOP_TIMER_DURATION = INCH_TIMER_DURATION + 2000;

        Timer* backupTimer;
        Timer* spinTimer;
        Timer* inchTimer;
        Timer* stopTimer;
        Timer* notSeenTimer;

    public:
        Strat(WorldState* _worldState, RobotActions* _robotActions);
        void run();
        void opponentInSight();
        void opponentLastKnownLocation();
        void opponentLocationUnknown();
        void onLine();
};

#endif