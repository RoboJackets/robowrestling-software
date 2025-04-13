#include "state/RobotState.h"
#include "action/RobotAction.h"
#include <Arduino.h>
#include "motor/MotorDriver.h"


MotorDriver *leftmotor;
MotorDriver *rightmotor;

void move_forwards(double speed){
    leftmotor->setSpeed(speed);
    rightmotor->setSpeed(speed);
    leftmotor->setdirection(0)
    rightmotor->setdirection(0);
    
}

void move_backwards(double speed) {
    rightmotor->setspeed(speed * -1);
    leftmotor->setspeed(speed * -1);
    rightmotor->setdirection(1);
    leftmotor->setdirection(1);
}

void move_left(double speed) {
    leftmotor->setSpeed(speed * -1);
    rightmotor->setSpeed(speed);
    leftmotor->setdirection(1);
    rightmotor->setdirection(0);
}

void move_right(double speed) {
    leftmotor->setSpeed(speed);
    rightmotor->setSpeed(speed * -1);
    leftmotor->setdirection(0);
    rightmotor->setdirection(1);
}
