#ifndef ROBOT_ACTIONS_H
#define ROBOT_ACTIONS_H
#include <stdint.h>

class robot_actions {
    private:
        int16_t* motors;

    public:
        robot_actions(int16_t* motors);
        void brake();
        void drive_forward(uint8_t speed);
        void drive_backward(uint8_t speed);
        void turn_left(uint8_t speed);
        void turn_right(uint8_t speed);
        void drive_custom(uint8_t LSpeed, uint8_t RSpeed, bool LDir, bool RDir);
};
#endif