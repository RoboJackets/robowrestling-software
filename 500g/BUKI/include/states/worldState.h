#ifndef WORLD_STATE_H_
#define WORLD_STATE_H_

#include "sensors/LINEsensor.h"
#include "sensors/IRsensor.h"

enum Edge {
    LEFT,
    SLIGHT_LEFT,
    RIGHT,
    SLIGHT_RIGHT,
    FRONT,
    BACK,
    SAFE
};

class WorldState {
    private:
        LINEsensor** lnsn;          // pointer to array of line sensors
        IRsensor** irsn;            // pointer to aray of IR sensors
    public:
        WorldState(LINEsensor*[], IRsensor*[]);     // Constructor: Takes arrays of pointers to LINEsensor and IRsensor objects
        Edge isNearEdge();                         // Function to check if the robot is near an edge and return the corresponding enum value
        int enemyDistance();                        
        void readSensors();   // do we need this? I think we read sensor values in "pollSensor" in main and then update the IR and Line sensor classes
        Edge enemyPos();                            // Function to check enemy Position and return enum value
};

#endif