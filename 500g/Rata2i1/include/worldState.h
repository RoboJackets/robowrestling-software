#ifndef WOLRD_STATE_H
#define WOLRD_STATE_H

#include "lineReader.h"
#include "irSensor.h"
#include "positionEnum.h"

class worldState {
    private:
        lineReader *frontLineSensor;
        lineReader *backLineSensor;
        IRSensor *frontLeftIRSensor;
        IRSensor *frontRightIRSensor;
        IRSensor *backLeftIRSensor;
        IRSensor *backRightIRSensor;
        Position EnemyPosition;

        //joebot sensors
        IRSensor *lSide;
        IRSensor *rSide;
        IRSensor *mSensor;

    public:
        struct robotSensors {
            lineReader *frontLineSensor;
            lineReader *backLineSensor;
            IRSensor *frontLeftIRSensor;
            IRSensor *frontRightIRSensor;
            IRSensor *backLeftIRSensor;
            IRSensor *backRightIRSensor;
        };
        worldState(robotSensors sensors);
        Position getEnemyPosition();
        Position getLastEnemyPosition();
        Position getPosition();


};

#endif