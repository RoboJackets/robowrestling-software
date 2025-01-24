#include <Sensors/irSensor.h>
#include <Sensors/lineSensor.h>
#include "Sensors/WorldState.h"

WorldState::WorldState(IrSensor *ir, LineSensor *line) {
    irStates = ir;
    lineStates = line;
}

EnemyPositions WorldState::getEnemyPosition() {
    return NoOp;
}

bool WorldState::getIsOnLine() {
    return 0;
}

