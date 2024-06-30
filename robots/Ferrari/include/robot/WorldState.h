#include "Sensors/IRSensor.h"
#include "Sensors/LineSensor.h"

#ifndef WORLD_STATE_H
#define WORLD_STATE_H

class WorldState {
    private:
        IRSensor* irSensor = new IRSensor[9];
        LineSensor* lineSensor = new LineSensor[8];
        LineSensor* plowSensor = new LineSensor[3];
    public:
        WorldState(IRSensor *irSensorArr, LineSensor *lineSensorArr, LineSensor *plowSensorArr);
        int getEnemyPosition();
        int getIsOnLine();
        bool getIsOnPlow();
};

#endif