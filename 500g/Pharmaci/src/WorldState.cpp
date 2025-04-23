
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

    if (middle && (leftMiddle || rightMiddle)) {
        return Position::Middle_Close;
    }

    if (middle) {
        return Position::Middle_Far;
    }

    if (left) {
        return Position::Left;
    }

    if (right) {
        return Position::Right;
    }

    // if (leftMiddle) {
    //     return Position::Left_Middle;
    // }

    // if (rightMiddle) {
    //     return Position::Right_Middle;
    // }

    return Position::None;
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