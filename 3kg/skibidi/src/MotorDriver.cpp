#include "MotorDriver.hpp"

MotorDriver::MotorDriver(int left_ctrl_1, int left_ctrl_2, int left_speed, int right_ctrl_1, int right_ctrl_2, int right_speed) {
    this->motor_pins[0][0] = left_ctrl_1;
    this->motor_pins[0][1] = left_ctrl_2;
    this->motor_pins[0][2] = left_speed;
    this->motor_pins[1][0] = right_ctrl_1;
    this->motor_pins[1][1] = right_ctrl_2;
    this->motor_pins[1][2] = right_speed;

    this->switch_millis = 0;
    this->switching = false;

    pinMode(motor_pins[0][0], OUTPUT);
    pinMode(motor_pins[0][1], OUTPUT);
    pinMode(motor_pins[0][2], OUTPUT);
    pinMode(motor_pins[1][0], OUTPUT);
    pinMode(motor_pins[1][1], OUTPUT);
    pinMode(motor_pins[1][2], OUTPUT);
}

inline int MotorDriver::map_to_pwm(int val) {
    /**
     *  OldRange = (OldMax - OldMin) = 100 - 0 = 100
     *  NewRange = (NewMax - NewMin) 255 - 0 = 255
     *
     *  NewValue = (((OldValue - OldMin) * NewRange) / OldRange) + NewMin
     *           = (((val - 0) * 255) / 100) + 0
     *           = ((val * 255) / 100)
     */
    return std::round(((val * 255) / 100));
}

void MotorDriver::change_state(DrivingState new_state) {
    if (this->switching || new_state != this->driving_state) {
        int mills = millis();

        if (!this->switching) {
            this->switching = true;
            this->switch_millis = mills;
        }

        if (mills - this->switch_millis >= SWITCH_WAIT_MILLIS) {
            this->driving_state = new_state;
            this->switching = false;
        } else {
            this->driving_state = DrivingState::MBRAKE;
        }

    } else {
        this->driving_state = new_state;
    }
}

inline void MotorDriver::drive(int speed) {
    this->drive(speed, speed);
}

void MotorDriver::drive(int left_speed, int right_speed) {
    std::array<int, 3> left_pins = this->motor_pins[0];
    std::array<int, 3> right_pins = this->motor_pins[1];

    switch (this->driving_state) {
        case MFORWARD:
            digitalWrite(left_pins[0], HIGH);
            digitalWrite(left_pins[1], LOW);
            digitalWrite(right_pins[0], HIGH);
            digitalWrite(right_pins[1], LOW);
            analogWrite(left_pins[2], this->map_to_pwm(left_speed));
            analogWrite(right_pins[2], this->map_to_pwm(right_speed));
            break;
        case MBACKWARD:
            digitalWrite(left_pins[0], LOW);
            digitalWrite(left_pins[1], HIGH);
            digitalWrite(right_pins[0], LOW);
            digitalWrite(right_pins[1], HIGH);
            analogWrite(left_pins[2], this->map_to_pwm(left_speed));
            analogWrite(right_pins[2], this->map_to_pwm(right_speed));
            break;
        // TODO: Make sure that these turn the bot correctly
        case MTURN_RIGHT:
            digitalWrite(left_pins[0], HIGH);
            digitalWrite(left_pins[1], LOW);
            digitalWrite(right_pins[0], LOW);
            digitalWrite(right_pins[1], HIGH);
            analogWrite(left_pins[2], this->map_to_pwm(left_speed));
            analogWrite(right_pins[2], this->map_to_pwm(right_speed));
            break;
        case MTURN_LEFT:
            digitalWrite(left_pins[0], LOW);
            digitalWrite(left_pins[1], HIGH);
            digitalWrite(right_pins[0], HIGH);
            digitalWrite(right_pins[1], LOW);
            analogWrite(left_pins[2], this->map_to_pwm(left_speed));
            analogWrite(right_pins[2], this->map_to_pwm(right_speed));
            break;
        case MCOAST:
            digitalWrite(left_pins[0], LOW);
            digitalWrite(left_pins[1], LOW);
            digitalWrite(right_pins[0], LOW);
            digitalWrite(right_pins[1], LOW);
            break;
        case MBRAKE:
            digitalWrite(left_pins[0], HIGH);
            digitalWrite(left_pins[1], HIGH);
            digitalWrite(right_pins[0], HIGH);
            digitalWrite(right_pins[1], HIGH);
            break;
    }
}
