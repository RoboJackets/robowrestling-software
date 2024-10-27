#pragma once
#include "../common.h"

class IMU {
    private:
        MPU6050 imu;
    public:
        IMU();
        // gyro data is returned in 16-bit 2's complement format
        int getAngleX();
        int getAngleY();
        int getAngleZ();
};