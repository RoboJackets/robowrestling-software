#ifndef WORLD_STATE_H_
#define WORLD_STATE_H_

#include "sensors/LINEsensor.h"
#include "sensors/IRsensor.h"

class WorldState {
    private:
        LINEsensor *lnsn[3];
        IRsensor *irsn[4];
    public:
        WorldState();
        short isNearEdge();
        int enemyDistance();
        void readSensors();
};

#endif