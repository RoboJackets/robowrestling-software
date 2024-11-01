#include "../../include/common.h"

IMU::IMU() : mpu(Wire) {
    byte status = mpu.begin(3, 0);
}

void IMU::update() {
    mpu.update();
}

// roll
float IMU::getAngleX() {
    return mpu.getAngleX();
}

// pitch
float IMU::getAngleY() {
    return mpu.getAngleY();
}

// yaw
float IMU::getAngleZ() {
    return mpu.getAngleZ();
}