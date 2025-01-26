#include <Arduino.h>

#ifndef IMU_H
#define IMU_H

class IMU {
    private:
        int pose;
    public:
        int getPose();

};

#endif