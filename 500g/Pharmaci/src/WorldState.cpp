
#include <WorldState.h>

WorldState::WorldState(LineSensor *frontLineSensorPointer, LineSensor *backLineSensorPointer,
        IRSensor *leftIRSensorPointer, IRSensor *leftMiddleIRSensorPointer, IRSensor
            *middleIRSensorPointer, IRSensor *rightMiddleIRSensorPointer, IRSensor *rightIRSensorPointer) {
    frontLineSensor = frontLineSensorPointer;
    backLineSensor = backLineSensorPointer;
    leftIRSensor = leftIRSensorPointer;
    leftMiddleIRSensor = leftMiddleIRSensorPointer;
    middleIRSensor = middleIRSensorPointer;
    rightMiddleIRSensor = rightMiddleIRSensorPointer;
    rightIRSensor = rightIRSensorPointer;
}