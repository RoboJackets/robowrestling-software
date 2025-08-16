#ifndef BACKSPINLEFT_H
#define BACKSPINLEFT_H

#include "utility/Action.hpp"
#include "utility/AutoTimer.hpp"
#include "RobotAction.h"

class BackSpinLeft : public Action {
    private:
        const int SPIN_DURATION = 400;
        const int BACKUP_DURATION = 250; 
        RobotAction *robotAction;
        AutoTimer *backup;
        AutoTimer *spin;
    protected:
        void performAction();
    public:
        BackSpinLeft(RobotAction *_robotAction);
};

#endif