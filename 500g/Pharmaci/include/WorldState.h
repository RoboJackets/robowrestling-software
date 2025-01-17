#ifndef WORLDSTATE_H
#define WORLDSTATE_H

#include "IRSensor.h"
#include "LineSensor.h"

class WorldState {
private:
    LineSensor *frontLineSensor;
    LineSensor *backLineSensor;

    IRSensor *leftIRSensor;
    IRSensor *leftMiddleIRSensor;
    IRSensor *middleIRSensor;
    IRSensor *rightMiddleIRSensor;
    IRSensor *rightIRSensor;

public:
    WorldState(LineSensor *frontLineSensorPointer, LineSensor *backLineSensorPointer,
        IRSensor *leftIRSensorPointer, IRSensor *leftMiddleIRSensorPointer, IRSensor
            *middleIRSensorPointer, IRSensor *rightMiddleIRSensorPointer, IRSensor *rightIRSensorPointer);

};

#endif