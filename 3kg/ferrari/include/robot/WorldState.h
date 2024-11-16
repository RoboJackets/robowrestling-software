#include "Sensors/IRSensor.h"
#include "Sensors/LineSensor.h"

#ifndef WORLD_STATE_H
#define WORLD_STATE_H

class WorldState {
    private:
        IRSensor* irSensor = new IRSensor[9];
        LineSensor* lineSensor = new LineSensor[8];
        LineSensor* plowSensor = new LineSensor[3];
        int enemyPosition;
        int lastEnemyPosition;
    public:
        WorldState(IRSensor *irSensorArr, LineSensor *lineSensorArr, LineSensor *plowSensorArr);

        // Defines the mapping between sensors and positions
        struct SensorPosition {
            int sensorIndex;
            int position;
        };
        static const SensorPosition sensorPositions[];
        
        int getEnemyPosition();
        int getLastEnemyPosition();
        int getIsOnLine();
        bool getIsOnPlow();
};

#endif