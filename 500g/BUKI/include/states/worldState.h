#ifndef WORLD_STATE_H_
#define WORLD_STATE_H_

#include "sensors/LINEsensor.h"
#include "sensors/IRsensor.h"

class WorldState {
    private:
        LINEsensor** lnsn;
        IRsensor** irsn;
    public:
        WorldState(LINEsensor*[], IRsensor*[]);
        short isNearEdge();
        int enemyDistance();
        void readSensors();
        void enemyPos(int*);
};

#endif