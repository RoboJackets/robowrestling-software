#ifndef ACTION_H
#define ACTION_H

#include "AutoTimer.hpp"

class Action {
    private:
        AutoTimer *actionTimer;
        bool actionInitiated;
        bool actionCompleted;
        int priority;
    protected:
        virtual void performAction() = 0;
    public:
        Action(int _actionDuration, int _priority);
        bool getActionCompleted();
        void run();
        void resetAction();
        int getPriority();
};

#endif