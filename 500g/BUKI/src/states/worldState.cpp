/* interprets binary outputs of sensors and abstracts them into more meaningful knowledge. 
use inumerations to describe lcoations and make a mapping. cycle thropugh mapping to return location of mapping */ 

#include "sensors/LINEsensor.h"
#include "sensors/IRsensor.h"
#include "states/worldState.h"

WorldState::WorldState(LINEsensor* linesensors[], IRsensor* irsensors[]) {      //constructor to initialize WorldState class with arrays of sensor objects
    lnsn = linesensors;
    irsn = irsensors;
    
}
void WorldState::readSensors() {
    // do some arduino stuff to set the sensor values based on pins

}
Edge WorldState::isNearEdge() {                        
    if ((lnsn[0]->getValue() < 200) && (lnsn[1]->getValue() < 200)) {       // Left and right sensors detect edge
        return FRONT;
    } else if (lnsn[1]->getValue() < 200) {                       // Right sensor detects edge
        return RIGHT;
    } else if (lnsn[0]->getValue() < 200) {                       // Left sensor detects edge
        return LEFT;
    } else if (lnsn[2]->getValue() < 200) {                       // Back sensor detects edge
        return BACK;
    } else {                                                // No sensor detects edge
        return SAFE;
    }
}

/** 
* @param list list of sensors, will update list based on which sensors are detecting the enemy
*/
Edge WorldState::enemyPos() {
    if (irsn[2]->getValue()) {       // Front sensors detect enemy
        return FRONT;
    } else if (irsn[0]->getValue()) {                       // Left sensor detects enemy
        return LEFT;
    } else if (irsn[1]->getValue()) {                       // Front right sensor detects enemy
        return SLIGHT_LEFT;
    } else if (irsn[3]->getValue()) {                       // Front left sensor detects enemy
        return SLIGHT_RIGHT;
    } else if (irsn[4]->getValue()) {                        // Right sensor detects enemy
        return RIGHT;
    } else if (irsn[1]->getValue() && irsn[2]->getValue() && irsn[3]->getValue()) {
        return CLOSE_FRONT;                                 // enemy is on top of us
    } else {                                                // No sensor detects enemy
        return SAFE;
    }


    // if (irsn[1]->getValue() && irsn[2]->getValue()) {       // Front sensors detect enemy
    //     return FRONT;
    // } else if (irsn[0]->getValue()) {                       // Left sensor detects enemy
    //     return LEFT;
    // } else if (irsn[1]->getValue()) {                       // Front right sensor detects enemy
    //     return SLIGHT_RIGHT;
    // } else if (irsn[2]->getValue()) {                       // Front left sensor detects enemy
    //     return SLIGHT_LEFT;
    // }else if (irsn[3]->getValue()) {                        // Right sensor detects enemy
    //     return RIGHT;
    // } else {                                                // No sensor detects enemy
    //     return SAFE;
    // }
    // return;
}