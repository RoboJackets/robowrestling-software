#ifndef TurnAround_H
#define TurnAround_H

#include "utility/Action.hpp"

class TurnAround : public Action {
    private:
        static constexpr int SPEED = 160;
        static constexpr int ACTION_DURATION = 360;
        RobotAction *robotAction;
    protected:
        void performAction();
        void resetTimers();
    public:
        TurnAround(RobotAction *_robotAction);
};

#endif