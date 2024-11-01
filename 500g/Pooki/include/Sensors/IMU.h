#pragma once
#include "../common.h"

class IMU {
    private:
        MPU6050 mpu;
    public:
        IMU();
        void update();
        // gyro data is returned in 16-bit 2's complement format
        float getAngleX();
        float getAngleY();
        float getAngleZ();
};