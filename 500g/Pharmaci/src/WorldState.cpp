
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
}

Position WorldState::getEnemyPosition() {
    int left = leftIRSensor->getValue();
    int leftMiddle = leftMiddleIRSensor->getValue();
    int middle = middleIRSensor->getValue();
    int rightMiddle = rightMiddleIRSensor->getValue();
    int right = rightIRSensor->getValue();

    if (leftMiddle && middle && rightMiddle) {
        return Position::Middle_Close;
    }

    if (!leftMiddle && middle && !rightMiddle) {
        return Position::Middle_Far;
    }

    if (left && !leftMiddle) {
        return Position::Left;
    }

    if (right && !rightMiddle) {
        return Position::Right;
    }

    if (leftMiddle) {
        return Position::Left_Middle;
    }

    if (rightMiddle) {
        return Position::RightMiddle;
    }

    return Position::None;
}

Position WorldState::getSelfPosition() {
    int left = leftLineSensor->getValue();
    int right = rightLineSensor->getValue();

    if (left) {
        return Position::On_Line_Left;
    } if (right) {
        return Position::On_Line_Right;
    }
    return Position::Off_Line;
}