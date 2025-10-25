#ifndef SCAN_H
#define SCAN_H

#include "utility/Action.hpp"

class Scan : public Action {
    private:
        static constexpr int SLOW_SPEED = 60;
        static constexpr int ACTION_DURATION = 1000;
        RobotAction *robotAction;
    protected:
        void performAction();
        void resetTimers();
    public:
        Scan(RobotAction *_robotAction);
};

#endif