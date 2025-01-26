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
        return FRONT;
    } else if (lnsn[1]->getValue()) {
        return RIGHT;
    } else if (lnsn[0]->getValue()) {
        return LEFT;
    } else if (lnsn[2]->getValue()) {
        return BACK;
    } else {
        return SAFE;
    }
}


/** 
* @param list list of sensors, will update list based on which sensors are detecting the enemy
*/
void WorldState::enemyPos(int* list) {
    list[0] = irsn[0]->getValue();
    list[1] = irsn[1]->getValue();
    list[2] = irsn[2]->getValue();
    list[3] = irsn[3]->getValue();
    return;
}