/* interprets binary outputs of sensors and abstracts them into more meaningful knowledge. 
use inumerations to describe lcoations and make a mapping. cycle thropugh mapping to return location of mapping */ 

#include "sensors/LINEsensor.h"
#include "sensors/IRsensor.h"
#include "states/worldState.h"
#include <cstdlib>

WorldState::WorldState() {
    for (int i = 0; i < 3; i++) {
        lnsn[i] = new LINEsensor();
    }
    for (int i = 0; i < 4; i++) {
        irsn[i] = new IRsensor();
    }
    
}
void WorldState::readSensors() {
    // do some arduino stuff to set the sensor values based on pins
}
short WorldState::isNearEdge() {
    if (lnsn[0]->getValue() && lnsn[1]->getValue()) {
        //  Edge in front
        return 4;
    } else if (lnsn[1]->getValue()) {
        // Edge to our right
        return 3;
    } else if (lnsn[0]->getValue()) {
        // Edge to our left
        return 2;
    } else if (lnsn[2]->getValue()) {
        // Edge begind us
        return 1;
    } else {
        // Not near an edge
        return 0;
    }
}
int WorldState::enemyDistance() {
    if (irsn[0]->isDetecting()) {
        return irsn[0]->getValue();
    } else if (irsn[1]->isDetecting()) {
        return irsn[1]->getValue();
    } else if (irsn[2]->isDetecting()) {
        return irsn[2]->getValue();
    } else if (irsn[3]->isDetecting()) {
        return irsn[3]->getValue();
    }
    return -1;
}