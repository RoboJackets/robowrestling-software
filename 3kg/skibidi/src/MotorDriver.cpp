#include "MotorDriver.hpp"

MotorDriver::MotorDriver(std::pair<int, int> right_pins, std::pair<int, int> left_pins) {
    this->motor_pins[0] = right_pins;
    this->motor_pins[1] = left_pins;

    pinMode(right_pins.first, OUTPUT);
    pinMode(right_pins.second, OUTPUT);
    pinMode(left_pins.first, OUTPUT);
    pinMode(left_pins.second, OUTPUT);
}

inline int MotorDriver::map_to_pwm(int val) {
    /**
     *  OldRange = (OldMax - OldMin) = 100 - (-100) = 200
     *  NewRange = (NewMax - NewMin) 255 - 0 = 255
     *
     *  NewValue = (((OldValue - OldMin) * NewRange) / OldRange) + NewMin
     *           = (((val - (-100)) * 255) / 200) + 0
     */
    return std::round((((val - (-100.0)) * 255) / 200));
}

void MotorDriver::change_state(DrivingState new_state) {
    this->driving_state = new_state;
}

void MotorDriver::drive(int speed) {
    std::pair<int, int> right_pins = this->motor_pins[0];
    std::pair<int, int> left_pins = this->motor_pins[1];

    switch (this->driving_state) {
        case MFORWARD:
            analogWrite(right_pins.first, this->map_to_pwm(-speed));
            analogWrite(right_pins.second, this->map_to_pwm(-speed));
            analogWrite(left_pins.first, this->map_to_pwm(speed));
            analogWrite(left_pins.second, this->map_to_pwm(speed));
            break;
        case MBACKWARD:
            analogWrite(right_pins.first, this->map_to_pwm(speed));
            analogWrite(right_pins.second, this->map_to_pwm(speed));
            analogWrite(left_pins.first, this->map_to_pwm(-speed));
            analogWrite(left_pins.second, this->map_to_pwm(-speed));
            break;
        // TODO: Make sure that these turn the bot correctly
        case MTURN_LEFT:
            analogWrite(right_pins.first, this->map_to_pwm(-speed));
            analogWrite(right_pins.second, this->map_to_pwm(-speed));
            analogWrite(left_pins.first, this->map_to_pwm(-speed));
            analogWrite(left_pins.second, this->map_to_pwm(-speed));
            break;
        case MTURN_RIGHT:
            analogWrite(right_pins.first, this->map_to_pwm(speed));
            analogWrite(right_pins.second, this->map_to_pwm(speed));
            analogWrite(left_pins.first, this->map_to_pwm(speed));
            analogWrite(left_pins.second, this->map_to_pwm(speed));
            break;
        case MCOAST:
            analogWrite(right_pins.first, 0);
            analogWrite(right_pins.second, 0);
            analogWrite(left_pins.first, 0);
            analogWrite(left_pins.second, 0);
            break;
        case MBRAKE:
            analogWrite(right_pins.first, 255);
            analogWrite(right_pins.second, 255);
            analogWrite(left_pins.first, 255);
            analogWrite(left_pins.second, 255);
            break;
    }
}
