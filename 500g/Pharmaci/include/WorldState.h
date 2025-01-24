#ifndef WORLDSTATE_H
#define WORLDSTATE_H

#include "IRSensor.h"
#include "LineSensor.h"
#include "Position.h"

class WorldState {
private:
    LineSensor *leftLineSensor;
    LineSensor *rightLineSensor;

    IRSensor *leftIRSensor;
    IRSensor *leftMiddleIRSensor;
    IRSensor *middleIRSensor;
    IRSensor *rightMiddleIRSensor;
    IRSensor *rightIRSensor;

public:
    WorldState(LineSensor *leftLineSensorPointer, LineSensor *rightLineSensorPointer,
        IRSensor *leftIRSensorPointer, IRSensor *leftMiddleIRSensorPointer, IRSensor
            *middleIRSensorPointer, IRSensor *rightMiddleIRSensorPointer, IRSensor *rightIRSensorPointer);
    Position getEnemyPosition();
    Position getSelfPosition();
};

#endif