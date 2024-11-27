#include "Sensors/IRSensor.h"
#include "Sensors/LineSensor.h"
#include "global-constants/EnemyPositionEnum.h"
#include "global-constants/IRSensorPositionEnum.h"
#include "global-constants/PlowSensorEnum.h"
#include "global-constants/LineSensorEnum.h"
#include "global-constants/RobotPositionEnum.h"

#ifndef WORLD_STATE_H
#define WORLD_STATE_H

class WorldState {
    private:
        IRSensor *irSensor = new IRSensor[9];
        LineSensor *lineSensor = new LineSensor[8];
        LineSensor *plowSensor = new LineSensor[3];
        EnemyPositionEnum enemyPosition;
        EnemyPositionEnum lastEnemyPosition;
    public:
        WorldState(IRSensor *irSensorArr, LineSensor *lineSensorArr, LineSensor *plowSensorArr);

        // Defines the mapping between sensors and positions
        struct SensorPosition {
            IRSensorPositionEnum sensorIndex;
            EnemyPositionEnum position;
        };
        static const SensorPosition sensorPositions[];
        
        EnemyPositionEnum getEnemyPosition();
        EnemyPositionEnum getLastEnemyPosition();
        RobotPositionEnum getIsOnLine();
        bool getIsOnPlow();
};

#endif