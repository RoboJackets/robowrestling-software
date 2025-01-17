/* interprets binary outputs of sensors and abstracts them into more meaningful knowledge. 
use inumerations to describe lcoations and make a mapping. cycle thropugh mapping to return location of mapping */ 

#include "sensors/LINEsensor.h"
#include "sensors/IRsensor.h"
#include "states/worldState.h"
#include <cstdlib>

WorldState::WorldState() {
    for (int i = 0; i < 3; i++) {
        lnsn[i] = (LINEsensor*) calloc(1, sizeof(LINEsensor));
    }

    for (int i = 0; i < 4; i++) {
        irsn[i] = (IRsensor*) calloc(1, sizeof(IRsensor));
    }
}
void WorldState::readSensors() {

}
short WorldState::isNearEdge() {

}
short WorldState::enemyDistance() {

}

void WorldState::apocalypse() {
    for (int i = 0; i < 3; i++) {
        free(lnsn[i]);
    }
    
    for (int i = 0; i < 4; i++) {
        free(irsn[i]);
    }
}