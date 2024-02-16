#ifndef WORLD_STATE_H
#define WORLD_STATE_H

#include "Sensors/LineSensor.h";
#include "Sensors/IRSensor.h";

class WorldState {
    private:
        LineSensor lineSensor;
        IRSensor irSensor;
    public:
        WorldState();
        
        int getEnemyPosition();
        int getLastEnemyPosition();
};

#endif


