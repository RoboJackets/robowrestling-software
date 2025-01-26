#ifndef MOTORDRIVER_HPP_
#define MOTORDRIVER_HPP_

#include <Arduino.h>
#include <cmath>
#include <utility>

enum DrivingState { FORWARD, BACKWARD, BRAKE, COAST };

class MotorDriver {
    private:
        DrivingState driving_state;
        std::pair<int, int> motor_pins[2];  // Make enum and change to map?

        inline int map_to_pwm(int val);
    public:
        MotorDriver(std::pair<int, int> right_pins, std::pair<int, int> left_pins);
        void change_state(DrivingState new_state);
        void drive(int speed);
};

#endif // MOTORDRIVER_HPP_
