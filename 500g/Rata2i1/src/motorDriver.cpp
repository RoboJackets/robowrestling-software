#include "motorDriver.h"
#include <Arduino.h>

//i copilioted all this, read datasheet later

motorDriver::motorDriver(){
    speed = 0;
    direction = true;
};
void motorDriver::setSpeed(int speed){
    this->speed = speed;
};
void motorDriver::setDirection(bool direction){
    this->direction = direction;
};
int motorDriver::getSpeed(){
    return this->speed;
};
bool motorDriver::getDirection(){
    return this->direction;
};