#ifndef WORLD_STATE_H
#define WORLD_STATE_H
#include "Zesti/include/SENSOR/lineSensor.h"
#include "Zesti/include/SENSOR/irSensor.h"

class WorldState {
private:
    int IrSensor[0];
    int LineSensor[0];

public:
    int getEnemyPosition();
    int getIsOnLine();
};

#endif // WORLD_STATE_H