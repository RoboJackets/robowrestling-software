
#include <WorldState.h>

WorldState::WorldState(LineSensor *leftLineSensorPointer, LineSensor *rightLineSensorPointer,
        IRSensor *leftIRSensorPointer, IRSensor *leftMiddleIRSensorPointer, IRSensor
            *middleIRSensorPointer, IRSensor *rightMiddleIRSensorPointer, IRSensor *rightIRSensorPointer) {
    leftLineSensor = leftLineSensorPointer;
    rightLineSensor = rightLineSensorPointer;
    leftIRSensor = leftIRSensorPointer;
    leftMiddleIRSensor = leftMiddleIRSensorPointer;
    middleIRSensor = middleIRSensorPointer;
    rightMiddleIRSensor = rightMiddleIRSensorPointer;
    rightIRSensor = rightIRSensorPointer;
    lastEnemyPosition = Position::Middle_Far;
}

Position WorldState::getEnemyPosition() {
    int left = leftIRSensor->getValue();
    int leftMiddle = leftMiddleIRSensor->getValue();
    int middle = middleIRSensor->getValue();
    int rightMiddle = rightMiddleIRSensor->getValue();
    int right = rightIRSensor->getValue();

    if (middle && leftMiddle && rightMiddle) {
        lastEnemyPosition = Position::Middle_Close;
        return Position::Middle_Close;
    }

    if (middle && leftMiddle && !rightMiddle) {
        lastEnemyPosition = Position::Left_Middle_Close;
        return Position::Left_Middle_Close;
    }
    
    if (middle && rightMiddle && !leftMiddle) {
        lastEnemyPosition = Position::Right_Middle_Close;
        return Position::Right_Middle_Close;
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

    if (rightMiddle) {
        lastEnemyPosition = Position::Right_Middle;
        return Position::Right_Middle;
    }

    if (leftMiddle) {
        lastEnemyPosition = Position::Left_Middle;
        return Position::Left_Middle;
    }

    return Position::None;
}

Position WorldState::getLastEnemyPosition() {
    return lastEnemyPosition;
}

Position WorldState::getSelfPosition() {
    int left = leftLineSensor->getValue();
    int right = rightLineSensor->getValue();
    if (left <= 600 && right <= 600) {
        return Position::On_Line;
    } else if (left <= 600) {
        return Position::On_Line_Left;
    } else if (right <= 600) {
        return Position::On_Line_Right;
    }
    return Position::Off_Line;
}