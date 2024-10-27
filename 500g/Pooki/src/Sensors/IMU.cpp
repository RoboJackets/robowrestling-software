#include "../../include/common.h"

IMU::IMU() : imu(MPU6050_DEFAULT_ADDRESS, &Wire) {
    Wire.begin();
    imu.initialize();
}

int IMU::getAngleX() {
    return imu.getRotationX();
}

int IMU::getAngleY() {
    return imu.getRotationY();
}

int IMU::getAngleZ() {
    return imu.getRotationZ();
}