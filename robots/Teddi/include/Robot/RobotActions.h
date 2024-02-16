#ifndef ROBOT_ACTIONS_H
#define ROBOT_ACTIONS_H

#include "MotorDriver.h";

class RobotActions {
    private:
        MotorDriver motorDriver;
    public:
        RobotActions();
        void moveForward();
        void moveSharpLeft();   //spin left
        void moveSharpRight();  //spin right
        void moveSoftLeft();    //both wheel still moving in the same direction but still a pretty sharp turn
        void moveSoftRight();
        void moveBackward();
        void moveSoftLeftBackward();    //less sharp turn because its only used to back up from the edge
        void moveSoftRightBackward();
};
#endif
