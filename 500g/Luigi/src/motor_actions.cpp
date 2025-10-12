#include <Arduino.h>
#include "motor_actions.hpp"

motor_actions::motor_actions(int* motors) {
    this -> motors = motors;
}

void motor_actions::driveForward(int speed) {
    motors[0] = speed; // Right motor speed
    motors[1] = speed; // Left motor speed
    return;
}

void motor_actions::driveBackward(int speed) {
    motors[0] = -speed; 
    motors[1] = -speed; 
    return;
}

void motor_actions::spinLeft(int speed) {
    motors[0] = speed; 
    motors[1] = -speed; 
    return;
}

void motor_actions::spinRight(int speed) {
    motors[0] = -speed; 
    motors[1] = speed; 
    return;
}

void motor_actions::stop() {
    motors[0] = 0; 
    motors[1] = 0; 
    return;
}
void motor_actions::customDrive(int rightSpeed, int leftSpeed) {
    motors[0] = rightSpeed; 
    motors[1] = leftSpeed; 
    return;
}

