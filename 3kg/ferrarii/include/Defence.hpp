#ifndef DEFENCE_H
#define DEFENCE_H

#include "WorldState.hpp"
#include "RobotActions.hpp"
#include "Speeds.hpp"
#include "Timer.hpp"

enum LastStateEnum{NONE, FAR};

class Defence {
    private:
        WorldState* worldState;
        RobotActions* robotActions;

        const int NOT_SEEN_TIMER_DURATION = 500;
        const int BACKUP_TIMER_DURATION = 300;
        const int SPIN_TIMER_DURATION = BACKUP_TIMER_DURATION + 100;
        const int INCH_TIMER_DURATION = 150;
        const int STOP_TIMER_DURATION = INCH_TIMER_DURATION + 2000;
        const int DASH_TIMER_DURATION = 500;

        Timer* backupTimer;
        Timer* spinTimer;
        Timer* inchTimer;
        Timer* stopTimer;
        Timer* notSeenTimer;
        Timer* dashTimer;

        bool has_dashed;
        LastStateEnum lastState;

    public:
        Defence(WorldState* _worldState, RobotActions* _robotActions);
        void run();
        void opponentInSight();
        void opponentLastKnownLocation();
        void opponentLocationUnknown();
        void onLine();
};

#endif