#ifndef BACKSPIN_H
#define BACKSPIN_H

#include "utility/Action.hpp"
#include "WorldState.h"

class BackSpin : public Action {
    private:
        static constexpr int LEFT_SPIN_DURATION = 80;
        static constexpr int RIGHT_SPIN_DURATION = 100;
        static constexpr int ACTION_DURATION = 500;
        bool spinLeft;
        RobotAction *robotAction;
        AutoTimer *backup;
        AutoTimer *spin;
    protected:
        void performAction();
        void resetTimers();
    public:
        BackSpin(RobotAction *_robotAction, bool _spinLeft);
};

#endif
