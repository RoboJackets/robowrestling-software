#include "sensors/MotorDriver.h"

MotorDriver::MotorDriver() {
    speed = 0;
    dir = 0;
}

MotorDriver::MotorDriver(int init_speed) {
    speed = init_speed;
}

MotorDriver::MotorDriver(int init_speed, int init_dir) {
    speed = init_speed;
    dir = init_dir;
}

bool MotorDriver::getDir() {
    return dir;
}

void MotorDriver::setDir(bool newdir) {
    dir = newdir;
}

int MotorDriver::getSpeed() {
    return speed;
}

void MotorDriver::setSpeed(int newspeed) {
    speed = newspeed;
}
