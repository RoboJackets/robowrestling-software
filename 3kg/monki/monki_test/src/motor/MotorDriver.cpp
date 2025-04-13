#include <Arduino.h>
#include "motor/MotorDriver.h"
#include <iostream>





void setdirecton(int direction) {
    // Set the motor direction based on the input parameter
    if (direction == 0) {
        // Set direction to forward
        digitalWrite(MOTOR_DIR_PIN, LOW);
    } else if (direction == -1) {
        // Set direction to backward
        digitalWrite(MOTOR_DIR_PIN, LOW);
    } else {
        std::cout << "You've entered an improper speed, please enter a valid direction, either 0 or 1" << std::endl;
        // Invalid direction, do nothing or handle error
    }
}
void setSpeed(int speed) {
    // Set the motor speed based on the input parameter
    if (speed >= 0 && speed <= 255) {
        analogWrite(MOTOR_PWM_PIN, speed); // Set PWM value for speed control
    } else {
        std::cout << "You've entered an improper speed, please enter a speed between -255 and 255" << std::endl;
    }
}
void stopMotor() {
    // Stop the motor by setting speed to 0
    setSpeed(0);
}

void getSpeed() {
    // Get the current speed of the motor (not implemented in this example)
    // You may need to implement a way to read the current speed if required
    return analogRead(MOTOR_PWM_PIN); // Example: read the PWM pin value
}
void getDirection() {
    // Get the current direction of the motor (not implemented in this example)
    // You may need to implement a way to read the current direction if required
    return digitalRead(MOTOR_DIR_PIN); // Example: read the direction pin value
}