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
        worldState(lineReader *frontLeftLineSensor, lineReader *frontRightLineSensor, lineReader *backLeftLineSensor, lineReader *backRightLineSensor, IRSensor *frontLeftIRSensor, IRSensor *frontRightIRSensor, IRSensor *Rside, IRSensor *Lside, IRSensor *MSensor);
        worldState(lineReader *frontLeftLineSensor, lineReader *frontRightLineSensor, lineReader *backLeftLineSensor, lineReader *backRightLineSensor, IRSensor *frontLeftIRSensor, IRSensor *frontRightIRSensor, IRSensor *backLeftIRSensor, IRSensor *backRightIRSensor);
        Position getEnemyPosition();
        Position getLastEnemyPosition();
        Position getPosition();


};

#endif