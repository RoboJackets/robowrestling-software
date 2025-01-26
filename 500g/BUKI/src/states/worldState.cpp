/* interprets binary outputs of sensors and abstracts them into more meaningful knowledge. 
use inumerations to describe lcoations and make a mapping. cycle thropugh mapping to return location of mapping */ 

#include "sensors/LINEsensor.h"
#include "sensors/IRsensor.h"
#include "states/worldState.h"
#include <cstdlib>

WorldState::WorldState(LINEsensor* linesensors[], IRsensor* irsensors[]) {
    lnsn = linesensors;
    irsn = irsensors;
    
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

/** 
* @param list list of sensors, will update list based on which sensors are detecting the enemy
*/
void WorldState::enemyPos(int* list) {
    if (irsn[0]->isDetecting()) {
        list[0] = 1;
    } else if (irsn[1]->isDetecting()) {
        list[1] = 1;
    } else if (irsn[2]->isDetecting()) {
        list[2] = 1;
    } else if (irsn[3]->isDetecting()) {
        list[3] = 1;
    }
    return;
}