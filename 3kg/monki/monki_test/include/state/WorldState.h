#include <Arduino.h>
#include "../sensors/IRSensor.h"
#include "../sensors/LineSensor.h"

#ifndef WORLD_STATE_H
#define WORLD_STATE_H

class WorldState {
    private:
        IrSensor ir_sensors[5];
        LineSensor line_sensors[2];
    public:
        
        int getEnemyPos();
        bool getAtBoundary();
};

#endif