#ifndef BACKSPINLEFT_H
#define BACKSPINLEFT_H

#include "utility/Action.hpp"
#include "utility/AutoTimer.hpp"
#include "RobotAction.h"

class BackSpinLeft : public Action {
    private:
        static constexpr int SPIN_DURATION = 80;
        static constexpr int BACKUP_DURATION = 400; 
        RobotAction *robotAction;
        AutoTimer *backup;
        AutoTimer *spin;
    protected:
        void performAction();
        void resetTimers();
    public:
        BackSpinLeft(RobotAction *_robotAction);
};

#endif