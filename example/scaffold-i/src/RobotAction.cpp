#include "RobotAction.h"
#define SPEED 100 

RobotAction::RobotAction(MotorDriver* motorDriver){
    this->motorDriver = motorDriver;
} 

void RobotAction::moveForward(int input) {
    motorDriver->setInput(input); 
    motorDriver->setSpeed(SPEED); 
}

void RobotAction::moveLeft(int input) {
    motorDriver->setInput(input); 
    motorDriver->setSpeed(SPEED);  
}

void RobotAction::moveRight(int input) {
    motorDriver->setInput(input);  
    motorDriver->setSpeed(SPEED);  
}

void RobotAction::moveBack(int input) {
    motorDriver->setInput(input); 
    motorDriver->setSpeed(SPEED);
}
