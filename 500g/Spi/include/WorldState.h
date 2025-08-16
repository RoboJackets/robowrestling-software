#ifndef WORLDSTATE_H
#define WORLDSTATE_H

#include "sensors/IRSensor.h"
#include "sensors/LineSensor.h"
#include "enumerations/PositionEnum.h"

class WorldState {
private:
    LineSensor *leftLineSensor;
    LineSensor *rightLineSensor;
    IRSensor *leftIRSensor;
    IRSensor *middleIRSensor;
    IRSensor *rightIRSensor;
    Position lastEnemyPosition;
    Position lastPosition;
public:
    WorldState(LineSensor *leftLineSensorPtr, LineSensor *rightLineSensorPtr, IRSensor *leftIRSensorPtr, IRSensor *middleIRSensorPtr, IRSensor *rightIRSensorPtr);
    Position getEnemyPosition();
    Position getLastEnemyPosition();
    Position getPosition();
    Position getLastPosition();
};

#endif