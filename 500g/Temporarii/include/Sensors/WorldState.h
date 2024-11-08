#include "Sensors/irSensor.cpp"
#include "Sensors/lineSensor.cpp"
#ifndef WORLDSTATE_H
#define WORLDSTATE_H

class WorldState{
    private:
        // Change size of the array to add multiple data points
        IrSensor irSensor[1];
        LineSensor lineSensor[1];
    public:
        int getEnemyPosition();
        int getIsOnLine();
};

#endif