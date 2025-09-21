#include "motorActions.hpp"

motorActions::motorActions(int* motors, int* irSensors, int* lineSensors) {
    this->motors = motors;
    this->irSensors = irSensors;
    this->lineSensors = lineSensors;
}


void motorActions:: driveForward(int speed) {
    
    motors[0] = speed; // Right motor speed
    motors[1] = speed; // Left motor speed
    return;
}

void motorActions:: driveBackward(int speed) {
    motors[0] = -speed; 
    motors[1] = -speed; 
    return;
}

void motorActions:: spinLeft(int speed) {
    motors[0] = speed; 
    motors[1] = -speed; 
    return;
}

void motorActions:: spinRight(int speed) {
    motors[0] = -speed; 
    motors[1] = speed; 
    return;
}

void motorActions:: stop() {
    motors[0] = 0; 
    motors[1] = 0; 
    return;
}
void motorActions::customDrive(int rightSpeed, int leftSpeed) {
    motors[0] = rightSpeed; 
    motors[1] = leftSpeed; 
    return;
}
void motorActions:: drive() {
    
    if (irSensors[0] == 1 && irSensors[1] == 1 && irSensors[2] == 1) { 
      driveForward(50);
    } else { 
       stop();
    }
    return;
}
