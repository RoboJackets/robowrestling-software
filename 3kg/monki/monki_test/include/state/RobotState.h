#include <Arduino.h>
#include "action/RobotAction.h"
#include "sensors/StartModule.h"
#include "sensors/IMU.h"
#include "EnemyPosition.h"
#include "../motor/MotorDriver.h"
#include "../sensors/LineSensor.h"
#include "../sensors/StartModule.h"

#ifndef ROBOT_STATE_H
#define ROBOT_STATE_H

class RobotState {

    // maybe include a separate robotstate struct

    private:
        RobotAction robotAction; 
        StartModule startModule;
        IMU imu;

    public:
        void calculateState();
};

#endif