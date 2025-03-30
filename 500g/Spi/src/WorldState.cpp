#include "WorldState.h"

WorldState::WorldState(LineSensor *leftLineSensorPtr, LineSensor *rightLineSensorPtr, IRSensor *leftIRSensorPtr, IRSensor *middleIRSensorPtr, IRSensor *rightIRSensorPtr) {
    leftLineSensor = leftLineSensorPtr;
    rightLineSensor = rightLineSensorPtr;
    leftIRSensor = leftIRSensorPtr;
    middleIRSensor = middleIRSensorPtr;
    rightIRSensor = rightIRSensorPtr;
    lastEnemyPosition = Position::Middle_Far;
}

Position WorldState::getEnemyPosition() {
    int left = leftIRSensor->getValue();
    int middle = middleIRSensor->getValue();
    int right = rightIRSensor->getValue();
    if (left && middle && right) {
        lastEnemyPosition = Position::Middle_Close;
        return Position::Middle_Close;
    }
    if (middle) {
        lastEnemyPosition = Position::Middle_Far;
        return Position::Middle_Far;
    }
    if (left) {
        lastEnemyPosition = Position::Left;
        return Position::Left;
    }
    if (right) {
        lastEnemyPosition = Position::Right;
        return Position::Right;
    }
    return Position::None;
}

Position WorldState::getLastEnemyPosition() {
    return lastEnemyPosition;
}

Position WorldState::getPosition() {
    // 1 when on line / white, 0 when not on line / black
    int left = (leftLineSensor->getValue());
    int right = (rightLineSensor->getValue());

    // LINE SENSORS BROKE RETURNING 0
    return Position::Off_Line;

    if (left) {
        return Position::On_Line_Left;
    }
    if (right) {
        return Position::On_Line_Right;
    }
    return Position::Off_Line;
}