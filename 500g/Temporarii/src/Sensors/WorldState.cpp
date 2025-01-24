#include <Sensors/irSensor.h>
#include <Sensors/lineSensor.h>
#include "Sensors/WorldState.h"

WorldState::WorldState(IrSensor *ir, LineSensor *line) {
    irStates = ir;
    lineStates = line;
    currPosition = NoOp;
}

EnemyPositions WorldState::getEnemyPosition() {
    int length = sizeof(irStates) / sizeof(irStates[0]);
    for (int i = 0; i < length; i++) {
        if (irStates[i].getValue() != 0) {
            // Convert values to ENUM values
            // SEND is when 3 sensors front activated
        }
    }
}

bool WorldState::getIsOnLine() {
    return 0;
}

