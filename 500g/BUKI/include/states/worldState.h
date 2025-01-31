#ifndef WORLD_STATE_H_
#define WORLD_STATE_H_

#include "sensors/LINEsensor.h"
#include "sensors/IRsensor.h"

enum Edge {
    LEFT,
    RIGHT,
    FRONT,
    BACK,
    SAFE
};

// add enumerations and integrate with functions. Ex: enumeration: EnemyPosition, and then EnemyPosition getEnemyPosition

class WorldState {
    private:
        LINEsensor** lnsn;          // pass array of pointers for IR and Line sensors
        IRsensor** irsn;
    public:
        WorldState(LINEsensor*[], IRsensor*[]);
        short isNearEdge();
        int enemyDistance();
        void readSensors();
        void enemyPos(int*);    
};

#endif