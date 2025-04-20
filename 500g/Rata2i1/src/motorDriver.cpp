#include "motorDriver.h"
#include <Arduino.h>

//i copilioted all this, read datasheet later

motorDriver::motorDriver(){
    speed = 0;
    fwd = 1;;
    bwd = 0;
};
void motorDriver::setSpeed(int speed){
    this->speed = speed;
};
void motorDriver::setDirection(bool direction){
    if (direction){
        this->fwd = 1;
        this->bwd = 0;
    } else {
        this->fwd = 0;
        this->bwd = 1;
    }
};
int motorDriver::getSpeed(){
    return this->speed;
};
bool motorDriver::getDirection(){
    if (fwd){
        return true;
    } else {
        return false;
    }
};