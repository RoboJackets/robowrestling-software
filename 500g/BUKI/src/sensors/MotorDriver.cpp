#include "sensors/MotorDriver.h"

MotorDriver::MotorDriver() {        // Constructor, initializes speed and direction to 0
    speed = 0;
    dir = 0;
}

MotorDriver::MotorDriver(int init_speed) {      // Constructor overloading (just for flexibility)
    speed = init_speed;
}

MotorDriver::MotorDriver(int init_speed, int init_dir) {    // Constructor overloading (just for flexibility)
    speed = init_speed;
    dir = init_dir;
}

bool MotorDriver::getDir() {    // stores dir in class (function)
    return dir;
}

void MotorDriver::setDir(bool newdir) {     // sets new dir in class (function)
    dir = newdir;
}

int MotorDriver::getSpeed() {   // stores speed in class (function)
    return speed;
}

void MotorDriver::setSpeed(int newspeed) {      // sets new speed in class (function)
    // possibly add some kind of conversion here, or add a completely new conversion method
    speed = newspeed;
}
