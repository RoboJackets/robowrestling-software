#include <Arduino.h>
#include "robotAction.h"

robotAction::robotAction(motorDriver *leftMotor, motorDriver *rightMotor){
    this->leftMotor = *leftMotor;
    this->rightMotor = *rightMotor;
};
void robotAction::moveForward(int speed){
    leftMotor.setSpeed(speed);
    rightMotor.setSpeed(speed);
    leftMotor.setDirection(true);
    rightMotor.setDirection(true);
    
};
void robotAction::moveBackward(int speed){
    leftMotor.setSpeed(speed);
    rightMotor.setSpeed(speed);
    leftMotor.setDirection(false);
    rightMotor.setDirection(false);
};
void robotAction::turnLeft(int speed){
    leftMotor.setSpeed(speed);
    rightMotor.setSpeed(speed);
    leftMotor.setDirection(false);
    rightMotor.setDirection(true);
};
void robotAction::turnRight(int speed){
    leftMotor.setSpeed(speed);
    rightMotor.setSpeed(speed);
    leftMotor.setDirection(true);
    rightMotor.setDirection(false);
};
void robotAction::stop(){
    leftMotor.setSpeed(0);
    rightMotor.setSpeed(0);
};
