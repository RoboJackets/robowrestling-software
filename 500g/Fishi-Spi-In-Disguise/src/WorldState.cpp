#include "WorldState.h"

WorldState::WorldState(LineSensor *leftLineSensorPtr, LineSensor *rightLineSensorPtr, IRSensor *leftIRSensorPtr, IRSensor *middleIRSensorPtr, IRSensor *rightIRSensorPtr) {
    leftLineSensor = leftLineSensorPtr;
    rightLineSensor = rightLineSensorPtr;
    leftIRSensor = leftIRSensorPtr;
    middleIRSensor = middleIRSensorPtr;
    rightIRSensor = rightIRSensorPtr;
    lastEnemyPosition = Position::None;
    lastPosition = Position::Off_Line;
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

/**
 * returns last enemy position
 * Options:
 * Middle_Close
 * Middle_Far
 * Left
 * Right
 */
Position WorldState::getLastEnemyPosition() {
    getEnemyPosition();
    return lastEnemyPosition;
}

Position WorldState::getPosition() {
    int left = (leftLineSensor->getValue());
    int right = (rightLineSensor->getValue());
    if (left && right) {
        lastPosition = Position::On_Line_Both;
        return Position::On_Line_Both;
    }
    if (left) {
        lastPosition = Position::On_Line_Left;
        return Position::On_Line_Left;
    }
    if (right) {
        lastPosition = Position::On_Line_Right;
        return Position::On_Line_Right;
    }
    return Position::Off_Line;
}

void WorldState::overrideLastPosition(Position position) {
    lastEnemyPosition = position;
}

Position WorldState::getLastPosition() {
    getPosition();
    return lastPosition;
}