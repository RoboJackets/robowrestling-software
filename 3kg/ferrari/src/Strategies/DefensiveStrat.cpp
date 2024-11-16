#include "robot/DefensiveStrat.h"
#include "robot/WorldState.h"
#include "global-constants/EnemyPositionEnum.h"
#include "global-constants/IRSensorPositionEnum.h"
#include "global-constants/PlowSensorEnum.h"
#include "global-constants/LineSensorEnum.h"
#include "global-constants/RobotPositionEnum.h"
#include "robot/RobotActions.h"
bool isDefensive= 1; //TRUE ! 
//Constructor implementation:
DefensiveStrat:: DefensiveStrat(WorldState*worldState, RobotActions*robotActions) {
    EnemyPositionEnum enemyPosition = worldState->getEnemyPosition();
    bool onPlow = worldState->getIsOnPlow();
};

void DefensiveStrat::watchingEnemy() {
//If any of the sensors read something that is not the front, we must turn so that the front sensor reads
    if (OP_NOT_FOUND) {
        robotActions->turnLeft(150);
        return;
    }
    if (OP_FAR_CENTER) {
        robotActions ->brake();
        //if it's in the far center, we do nothing
        return;
    }
    if (OP_LEFT_90){
        robotActions -> turnRight(255);
        return;
    }
    if (OP_RIGHT_90){ 
        robotActions -> turnLeft(255);
        return;
    }
    if (OP_RIGHT_30 || OP_RIGHT_60 || OP_RIGHT_45) {
        robotActions -> turnLeft(150);
        return;
    }
    if (OP_LEFT_45 || OP_LEFT_60 || OP_LEFT_30) {
        robotActions ->turnRight(150);
        return;
    }
};

// void DefensiveStrat::charge() {
//     //If the IR sensor at the front detects something, then go forwards


// };

// void DefensiveStrat:: fullThrottle() {
//     //If the front IR sensor and the line sensors on the plow detect something, go full power (255!!!!!!)
// };

void DefensiveStrat::runAway() {
    // if the side sensors detect something, then scoot forward or backwards (most likely forwards in defensive strategy)
    //Place somewhere towards the middle back of our side if we are running the defensive strategy, away from their field of vision
    if (OP_LEFT_90 || OP_RIGHT_90){ 
        robotActions -> driveForward(100);
    } else {
        robotActions -> brake();
    }
};