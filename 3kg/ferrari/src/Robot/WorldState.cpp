#include "robot/WorldState.h"

WorldState::WorldState(IRSensor *irSensorArr, LineSensor *lineSensorArr, LineSensor *plowSensorArr) {
    irSensor = irSensorArr;
    lineSensor = lineSensorArr;
    plowSensor = plowSensorArr;
    enemyPosition = OP_NOT_FOUND;
    lastEnemyPosition = OP_NOT_FOUND;
}

/**
 * Mapping between sensors and enemy position
 */
const WorldState::SensorPosition WorldState::sensorPositions[] = {
    {CENTER_IR, OP_FAR_CENTER},
    {LEFT_IR_90, OP_LEFT_90},
    {LEFT_IR_30, OP_LEFT_30},
    {RIGHT_IR_30, OP_RIGHT_30},
    {RIGHT_IR_90, OP_RIGHT_90}
};

/**
 * Sets and returns the enemy position.
 */
EnemyPositionEnum WorldState::getEnemyPosition() {

    // Special cases
    if (irSensor[CENTER_IR].getValue() == 1 
        && plowSensor->getValue() == 1) {
        return lastEnemyPosition = OP_ON_PLOW;
    }
    if (irSensor[CENTER_IR].getValue() == 1 
        && irSensor[LEFT_IR_30].getValue() == 1 
        && irSensor[RIGHT_IR_30].getValue() == 1) {
        return lastEnemyPosition = OP_CLOSE_CENTER;
    }

    // Check each sensor
    for (const SensorPosition sensorPos : sensorPositions) {
        if (irSensor[sensorPos.sensorIndex].getValue() == 1) {
            return lastEnemyPosition = sensorPos.position;
        }
    }

    // No ops? D:
    return OP_NOT_FOUND;
}

/**
 * Returns where the enemy was last seen.
 */
EnemyPositionEnum WorldState::getLastEnemyPosition() {
    getEnemyPosition();
    return lastEnemyPosition;
}

/**
 * Returns if and where Ferrari is on the line
 */
RobotPositionEnum WorldState::getIsOnLine() {
    if (lineSensor[TOP_LEFT_1].getValue() == 1 && lineSensor[TOP_LEFT_2].getValue() == 1) {
        return ON_LINE_TOP_LEFT;
    }
    if (lineSensor[TOP_RIGHT_1].getValue() == 1 && lineSensor[TOP_RIGHT_2].getValue() == 1) {
        return ON_LINE_TOP_RIGHT;
    }
    if (lineSensor[BOTTOM_LEFT].getValue()) {
        return ON_LINE_BOTTOM_LEFT;
    }
    if (lineSensor[BOTTOM_RIGHT].getValue()) {
        return ON_LINE_BOTTOM_RIGHT;
    }
    return NOT_ON_LINE;
}