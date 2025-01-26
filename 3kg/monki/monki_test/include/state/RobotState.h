#include <Arduino.h>
#include "../common.h"

#ifndef ROBOT_STATE_H
#define ROBOT_STATE_H

class RobotState {

    // maybe include a separate robotstate struct

    private:
        RobotAction robotAction; 
        StartModule startModule;
        CurrentSensor currentSensor;
        IMU imu;

    public:
        void calculateState();
};

#endif