#include <Sensors/irSensor.h>
#include <Sensors/lineSensor.h>
#include "Sensors/WorldState.h"

WorldState::WorldState(IrSensor *ir[5], LineSensor *line[4]) {
    for (int i = 0; i < 5; i++) {
        irStates[i] = *ir[i];
    }
    for (int i = 0; i < 4; i++) {
        lineStates[i] = *line[i];
    }
    currPosition = NoOp;
}

WorldState::WorldState() {
    currPosition = NoOp;
}

EnemyPositions WorldState::getEnemyPosition() {
    // IrSensor Array = {Left, MidLeft, Mid, MidRight, Right}
    // Middle pins all on is full Sends
    if (irStates[1].getValue() == 1 && irStates[2].getValue() == 1 && irStates[3].getValue() == 1) {
        return SEND;
    }
    if (irStates[0].getValue() == 1) {
        return Left;
    }
    if (irStates[1].getValue() == 1) {
        return MidL;
    }
    if (irStates[2].getValue() == 1) {
        return Mid;
    }
    if (irStates[3].getValue() == 1) {
        return MidR;
    }
    if (irStates[4].getValue() == 1) {
        return Right;
    }
    return NoOp;
}

OnLine WorldState::getIsOnLine() {
    // Line Sensors Array = [Top Left, Top Right, Back Left, Back Right]
    // Test reading from circle to get white and black values (0 is black and 1000 is white)
    if (lineStates[0].getValue() >= 700) {
        return left_front_on_line;
    } else if (lineStates[1].getValue() >= 700) {
        return right_front_on_line;
    } else if (lineStates[2].getValue() >= 700) {
        return left_on_line;
    } else if (lineStates[3].getValue() >= 700) {
        return right_on_line;
    }
    return not_on_line;
}

