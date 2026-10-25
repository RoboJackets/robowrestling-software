#include <Arduino.h>
#include "motor_actions.hpp"

motor_actions::motor_actions(int* motors) {
    this->motors = motors;
}

void motor_actions::driveForward(int speed) {
    motors[0] = speed; 
    motors[1] = speed; 
}

void motor_actions::driveBackward(int speed) {
    motors[0] = -speed; 
    motors[1] = -speed; 
}

void motor_actions::spinLeft(int speed) {
    motors[1] = speed; 
    motors[0] = -speed; 
}

void motor_actions::spinRight(int speed) {
    motors[1] = -speed; 
    motors[0] = speed; 
}

void motor_actions::stop() {
    motors[0] = 0; 
    motors[1] = 0; 
}

void motor_actions::customDrive(int rightSpeed, int leftSpeed) {
    motors[1] = rightSpeed; 
    motors[0] = leftSpeed; 
}