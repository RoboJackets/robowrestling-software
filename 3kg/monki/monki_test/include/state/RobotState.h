#include <Arduino.h>
#include "../action/RobotAction.h"

#ifndef ROBOT_STATE_H
#define ROBOT_STATE_H

class RobotState {
    
    private:
       RobotAction robotAction; 

    public:
        void calculateState();
};

#endif