#ifndef BACKSPINRIGHT_H
#define BACKSPINRIGHT_H

#include "utility/Action.hpp"
#include "utility/AutoTimer.hpp"
#include "RobotAction.h"

class BackSpinRight : public Action {
    private:
        static constexpr int SPIN_DURATION = 100;
        static constexpr int BACKUP_DURATION = 400; 
        RobotAction *robotAction;
        AutoTimer *backup;
        AutoTimer *spin;
    protected:
        void performAction();
        void resetTimers();
    public:
        BackSpinRight(RobotAction *_robotAction);
};

#endif