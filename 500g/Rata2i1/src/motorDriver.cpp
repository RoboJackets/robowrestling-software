#include "motorDriver.h"
#include <Arduino.h>

//i copilioted all this, read datasheet later

motorDriver::motorDriver(){
    speed = 0;
    direction = 0;
};
void motorDriver::setSpeed(int speed){
    this->speed = speed;
};
void motorDriver::setDirection(int direction){
    this->direction = direction;
};
void motorDriver::stop(){
    this->speed = 0;
    this -> direction = 0;
};
int motorDriver::getSpeed(){
    return this->speed;
};
bool motorDriver::getDirection(){
    return this->direction;
};