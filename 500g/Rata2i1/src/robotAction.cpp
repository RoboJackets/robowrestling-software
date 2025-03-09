#include <Arduino.h>
#include "robotAction.h"

robotAction::robotAction(motorDriver *leftMotor, motorDriver *rightMotor){
    this->leftMotor = leftMotor;
    this->rightMotor = rightMotor;
};
void robotAction::moveForward(int speed){
    leftMotor->setSpeed(speed);
    rightMotor->setSpeed(speed);
    leftMotor->setDirection(true);
    rightMotor->setDirection(true);
};
void robotAction::moveForwardFor(int speed, int time){
    moveForward(speed);
    delay(time);
    stop();
};
void robotAction::moveBackward(int speed){
    leftMotor->setSpeed(speed);
    rightMotor->setSpeed(speed);
    leftMotor->setDirection(false);
    rightMotor->setDirection(false);
};
void robotAction::moveBackwardFor(int speed, int time){
    moveBackward(speed);
    delay(time);
    stop();
};
void robotAction::turnLeft(int speed){
    leftMotor->setSpeed(speed);
    rightMotor->setSpeed(speed);
    leftMotor->setDirection(false);
    rightMotor->setDirection(true);
};
void robotAction::turnLeftFor(int speed, int time){
    turnLeft(speed);
    delay(time);
    stop();
};
void robotAction::turnRight(int speed){
    leftMotor->setSpeed(speed);
    rightMotor->setSpeed(speed);
    leftMotor->setDirection(true);
    rightMotor->setDirection(false);
};
void robotAction::turnRightFor(int speed, int time){
    turnRight(speed);
    delay(time);
    stop();
};
void robotAction::stop(){
    leftMotor->setSpeed(0);
    rightMotor->setSpeed(0);
    leftMotor->setDirection(true);
    rightMotor->setDirection(true);
};
