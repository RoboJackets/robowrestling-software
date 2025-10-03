#ifndef MOTORDRIVER_HPP_
#define MOTORDRIVER_HPP_

#include <Arduino.h>
#include <array>
#include <cmath>
#include <utility>

#define SWITCH_WAIT_MILLIS 5

enum DrivingState { MFORWARD, MBACKWARD, MTURN_LEFT, MTURN_RIGHT, MBRAKE, MCOAST };

class MotorDriver {
    private:
        std::array<std::array<int, 3>, 2> motor_pins;  // Make enum and change to map?
        int  switch_millis;
        bool switching;

        inline int map_to_pwm(int val);

    public:
        DrivingState driving_state;
        MotorDriver(int left_ctrl_1, int left_ctrl_2, int left_speed, int right_ctrl_1, int right_ctrl_2, int right_speed);
        void change_state(DrivingState new_state);
        inline void drive(int speed);
        void drive(int left_speed, int right_speed);
};

#endif // MOTORDRIVER_HPP_
