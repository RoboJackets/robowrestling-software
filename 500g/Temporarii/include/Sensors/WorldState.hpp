#include "Sensors/IrSensor.hpp"
#include "Sensors/lineSensor.hpp"
#include "Enumerations/EnemyPositions.hpp"
#include "Enumerations/OnLine.hpp"

#ifndef WORLDSTATE_HPP
#define WORLDSTATE_HPP

class WorldState {
    private:
        // IrSensor Array = {Left, MidLeft, Mid, MidRight, Right}
        IrSensor *irStates[5];
        // LineSensor Array = {FrontLeft, BackLeft, FrontRight, BackRight};
        LineSensor *lineStates[4];
        EnemyPositions currPosition;

    public:
        WorldState(IrSensor *ir[5], LineSensor *line[4]);
        WorldState();
        // IrSensor getIRStates();
        EnemyPositions getEnemyPosition();
        OnLine getIsOnLine();
};

#endif