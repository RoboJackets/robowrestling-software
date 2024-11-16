#include "robot/DefensiveStrat.h"
#include "robot/WorldState.h"
#include "global-constants/EnemyPositionEnum.h"
#include "global-constants/IRSensorPositionEnum.h"
#include "global-constants/PlowSensorEnum.h"
#include "global-constants/LineSensorEnum.h"
#include "global-constants/RobotPositionEnum.h"

bool isDefensive= 1; //TRUE ! 
//Constructor implementation:
DefensiveStrat:: DefensiveStrat(WorldState*worldState) {
    EnemyPositionEnum enemyPosition = worldState->getEnemyPosition();
    bool onPlow = worldState->getIsOnPlow();

};

void DefensiveStrat::watchingEnemy() {
//If any of the sensors read something that is not the front, we must turn so that the front sensor reads
if (OP_NOT_FOUND) {


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

};