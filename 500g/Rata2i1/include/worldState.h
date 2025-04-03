#ifndef WOLRD_STATE_H
#define WOLRD_STATE_H

#include "lineReader.h"
#include "irSensor.h"
#include "positionEnum.h"

class worldState {
    private:
        lineReader *frontLeftLineSensor;
        lineReader *frontRightLineSensor;
        lineReader *backLeftLineSensor;
        lineReader *backRightLineSensor;
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
        //joe worldstate
        struct joebotSensors {
            lineReader *frontLeftLineSensor;
            lineReader *frontRightLineSensor;
            IRSensor *frontLeftIRSensor;
            IRSensor *frontRightIRSensor;
            IRSensor *Rside;
            IRSensor *Lside;
        };
        struct joebotSensors {
            lineReader *frontLeftLineSensor;
            lineReader *frontRightLineSensor;
            lineReader *backLeftLineSensor;
            lineReader *backRightLineSensor;
            IRSensor *frontLeftIRSensor;
            IRSensor *frontRightIRSensor;
            IRSensor *Rside;
            IRSensor *Lside;
            IRSensor *MSensor;
        };
        struct robotSensors {
            lineReader *frontLeftLineSensor;
            lineReader *frontRightLineSensor;
            lineReader *backLeftLineSensor;
            lineReader *backRightLineSensor;
            IRSensor *frontLeftIRSensor;
            IRSensor *frontRightIRSensor;
            IRSensor *backLeftIRSensor;
            IRSensor *backRightIRSensor;
        };
        worldState(joebotSensors sensors);
        worldState(robotSensors sensors);
        Position getEnemyPosition();
        Position getLastEnemyPosition();
        Position getPosition();


};

#endif