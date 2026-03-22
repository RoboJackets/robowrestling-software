#ifndef ROBOT_ACTIONS_H
#define ROBOT_ACTIONS_H

class robot_actions {
    private:
        int* motors;
        int acceleration;

    public:
        robot_actions(int* motors);
        void brake();
        void drive_forward(int speed);
        void drive_backward(int speed);
        void turn_left(int speed);
        void turn_right(int speed);
        void drive_custom(int LSpeed, int RSpeed, bool LDir, bool RDir);
};
#endif