#include <Arduino.h>
#include "robotAction.h"

class robotAction {
    private:
        motorDriver leftMotor;
        motorDriver rightMotor;
    public:
        robotAction(){
            leftMotor = motorDriver();
            rightMotor = motorDriver();
        };
        void moveForward(int speed){
            leftMotor.setSpeed(speed);
            rightMotor.setSpeed(speed);
            
        };
        void moveBackward(int speed){
            leftMotor.setSpeed(speed);
            rightMotor.setSpeed(speed);
            leftMotor.setDirection(false);
            rightMotor.setDirection(false);
        };
        void turnLeft(int speed){
            leftMotor.setSpeed(speed);
            rightMotor.setSpeed(speed);
            leftMotor.setDirection(false);
            rightMotor.setDirection(true);
        };
        void turnRight(int speed){
            leftMotor.setSpeed(speed);
            rightMotor.setSpeed(speed);
            leftMotor.setDirection(true);
            rightMotor.setDirection(false);
        };
        void stop(){
            leftMotor.stop();
            rightMotor.stop();
        };
};