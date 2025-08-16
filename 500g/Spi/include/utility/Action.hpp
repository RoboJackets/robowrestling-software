#ifndef ACTION_H
#define ACTION_H

#include "AutoTimer.hpp"
#include "RobotAction.h"

class Action {
    private:
        AutoTimer *actionTimer;
        RobotAction *robotAction;
        bool actionInitiated;
        bool actionCompleted;
        int priority;
    protected:
        virtual void performAction() = 0;
    public:
        Action(int _actionDuration, int _priority, RobotAction *_robotAction);
        bool getActionCompleted();
        void run();
        void resetAction();
        int getPriority();
};

#endif