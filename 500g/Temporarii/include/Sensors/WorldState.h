#ifndef WORLDSTATE_H
#include "Sensors/irSensor.h"
#include "Sensors/lineSensor.h"
#include "Enumerations/EnemyPositions.hpp"
#include "Enumerations/OnLine.hpp"
#define WORLDSTATE_H

class WorldState{
    private:
        // IrSensor Array = {Left, MidLeft, Mid, MidRight, Right}
        IrSensor irStates[5];
        // LineSensor Array = {FrontLeft, BackLeft, FrontRight, BackRight};
        LineSensor lineStates[4];
        EnemyPositions currPosition;
    public:
        WorldState(IrSensor *ir[5], LineSensor *line[4]);
        WorldState();
        EnemyPositions getEnemyPosition();
        OnLine getIsOnLine();
};

#endif