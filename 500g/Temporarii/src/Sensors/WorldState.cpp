#include "Sensors/IrSensor.hpp"
#include "Sensors/lineSensor.hpp"
#include "Sensors/WorldState.hpp"

// Constructor w/ Parameter
WorldState::WorldState(IrSensor *ir[5], LineSensor *line[4]) {
    for (int i = 0; i < 5; i++) {
        irStates[i] = ir[i];
    }
    for (int i = 0; i < 4; i++) {
        lineStates[i] = line[i];
    }
    currPosition = EnemyNone;
}

// Constructor Default
WorldState::WorldState() {
    currPosition = EnemyNone;
}

// Get Enemy Position
EnemyPositions WorldState::getEnemyPosition() {
    // IrSensor Array = {Left, MidLeft, Mid, MidRight, Right}
    if (irStates[1]->getValue() == 1 && irStates[2]->getValue() == 1 && irStates[3]->getValue() == 1) {
        currPosition = EnemyFront;
        return EnemyFront;
    } else if (irStates[0]->getValue() == 1) {
        currPosition = EnemyLeft;
        return EnemyLeft;
    } else if (irStates[1]->getValue() == 1) {
        currPosition = EnemyFL;
        return EnemyFL;
    } else if (irStates[2]->getValue() == 1) {
        currPosition = EnemyFront;
        return EnemyFront;
    } else if (irStates[3]->getValue() == 1) {
        currPosition = EnemyFR;
        return EnemyFR;
    } else if (irStates[4]->getValue() == 1) {
        currPosition = EnemyRight;
        return EnemyRight;
    }
    currPosition = EnemyNone;
    return EnemyNone;
}

// Get whether we are on line
OnLine WorldState::getIsOnLine() {
    // Line Sensors Array = [Back Left, Front Left, Front Right, Back Right]
    // Test reading from circle to get white and black values (0 is black and 1000 is white)
    // Tested for circular platform ~950 for black and <700 for white
    if (lineStates[0]->getValue() <= 900) {
        return LineBL;
    } else if (lineStates[1]->getValue() <= 900) {
        return LineFL;
    } else if (lineStates[2]->getValue() <= 900) {
        return LineFR;
    } else if (lineStates[3]->getValue() <= 900) {
        return LineBR;
    }
    return LineNone;
}