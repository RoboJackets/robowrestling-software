#include "robot_actions.hpp"
#include <Arduino.h>


robot_actions::robot_actions(int* motor_vals) {
    motors = motor_vals;
}

void robot_actions::applyMotors() {
    if (motors[0] > 0 && motors[1] > 0) {
    //forward
    digitalWrite(leftDIR, HIGH);
    analogWrite(leftPWM, motors[0]);
    digitalWrite(rightDIR, HIGH);
    analogWrite(rightPWM, motors[1]);
  } else if (motors[0] < 0 && motors[1] < 0) {
    //backward
    digitalWrite(leftDIR, LOW);
    analogWrite(leftPWM, -motors[0]);
    digitalWrite(rightDIR, LOW);
    analogWrite(rightPWM, -motors[1]);
  } else if (motors[0] > 0 && motors[1] < 0) {
    //turn right
    digitalWrite(leftDIR, HIGH);
    analogWrite(leftPWM, motors[0]);
    digitalWrite(rightDIR, LOW);
    analogWrite(rightPWM, -motors[1]);
  } else if (motors[0] < 0 && motors[1] > 0) {
    //turn left
    digitalWrite(leftDIR, LOW);
    analogWrite(leftPWM, -motors[0]);
    digitalWrite(rightDIR, HIGH);
    analogWrite(rightPWM, motors[1]);
  } else {
    //brake
    digitalWrite(leftDIR, HIGH);
    analogWrite(leftPWM, 255);
    digitalWrite(rightDIR, HIGH);
    analogWrite(rightPWM, 255);
  }
}

void robot_actions::brake() {
    motors[0] = 0;
    motors[1] = 0;
}

void robot_actions::drive_forward(int speed) {
    motors[0] = speed;
    motors[1] = speed;
}

void robot_actions::drive_backward(int speed) {
    motors[0] = -speed;
    motors[1] = -speed;
}
void robot_actions::drive_right(int speed) {
    motors[0] = speed;
    motors[1] = -speed;
}
void robot_actions::drive_left(int speed) {
    motors[0] = -speed;
    motors[1] = speed;
}


