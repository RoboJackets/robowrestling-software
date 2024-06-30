#include "robot/WorldState.h"
#include "global-constants/EnemyPositionEnum.h"
#include "global-constants/IRSensorPositionEnum.h"
#include "global-constants/PlowSensorEnum.h"
#include "global-constants/LineSensorEnum.h"
#include "global-constants/RobotPositionEnum.h"

WorldState::WorldState(IRSensor *irSensorArr, LineSensor *lineSensorArr, LineSensor *plowSensorArr) {
    irSensor = irSensorArr;
    lineSensor = lineSensorArr;
    plowSensor = plowSensorArr;
}

int WorldState::getEnemyPosition() {
    if (irSensor[CENTER_IR].getValue() == 1
    && getIsOnPlow()) {
        return OP_ON_PLOW;
    }
    if (irSensor[CENTER_IR].getValue() == 1 
    && irSensor[LEFT_IR_IN].getValue() == 1 
    && irSensor[RIGHT_IR_IN].getValue() == 1) {
        return OP_CLOSE_CENTER;
    }
    if (irSensor[CENTER_IR].getValue() == 1) {
        return OP_FAR_CENTER;
    }
    if (irSensor[LEFT_IR_90].getValue() == 1) {
        return OP_LEFT_90;
    }
    if (irSensor[LEFT_IR_60].getValue() == 1) {
        return OP_LEFT_60;
    }
    if (irSensor[LEFT_IR_45].getValue() == 1) {
        return OP_LEFT_45;
    }
    if (irSensor[RIGHT_IR_45].getValue() == 1) {
        return OP_RIGHT_45;
    }
    if (irSensor[RIGHT_IR_60].getValue() == 1) {
        return OP_RIGHT_60;
    }
    if (irSensor[RIGHT_IR_90].getValue() == 1) {
        return OP_RIGHT_90;
    }
    return -1;
}

int WorldState::getIsOnLine() {
    if (lineSensor[TOP_LEFT_1].getValue() == 1 && lineSensor[TOP_LEFT_2].getValue() == 1) {
        return ON_LINE_TOP_LEFT;
    }
    if (lineSensor[TOP_RIGHT_1].getValue() == 1 && lineSensor[TOP_RIGHT_2].getValue() == 1) {
        return ON_LINE_TOP_RIGHT;
    }
    if (lineSensor[BOTTOM_LEFT_1].getValue() == 1 && lineSensor[BOTTOM_LEFT_2].getValue() == 1) {
        return ON_LINE_BOTTOM_LEFT;
    }
    if (lineSensor[BOTTOM_RIGHT_1].getValue() == 1 && lineSensor[BOTTOM_RIGHT_2].getValue() == 1) {
        return ON_LINE_BOTTOM_RIGHT;
    }
}

bool WorldState::getIsOnPlow() {
    int plowSensorsOn;
    for (int i = 0; i < sizeof(plowSensor) / sizeof(lineSensor); i++) { //might want to double check that sizeof(plowSensor) / sizeof(lineSensor) == 3
        if (plowSensor[i].getValue() == 1) {
            plowSensorsOn++;
        }
    }
    return plowSensorsOn >= 2;
}