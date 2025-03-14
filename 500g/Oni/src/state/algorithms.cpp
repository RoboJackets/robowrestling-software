#include "state/algorithms.h"
#include "enums/state_enums.h"

algorithms :: algorithms(RobotAction *roboAct, world_state * worldSta) {
    this -> roboAction = roboAct;
    this -> worldState = worldSta;
}

void algorithms :: go_forward() {
    if(worldState-> enemy_location() == MIDDLE){
        roboAction->medForward();
    }
    else if (worldState->enemy_location() == NOTHING){
        roboAction -> stop();
    }
}
