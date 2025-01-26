#include "Sensors/irSensor.cpp"
#include "Sensors/lineSensor.cpp"
#include "Enumerations/EnemyPositions.hpp"
#ifndef WORLDSTATE_H
#define WORLDSTATE_H

class WorldState{
    private:
        IrSensor *Mid;
        IrSensor *MidL;
        IrSensor *MidR;
        IrSensor *Left;
        IrSensor *Right;

        LineSensor *TopL;
        LineSensor *TopR;
        LineSensor *BackL;
        LineSensor *BackR;

        // Change size of the array to add multiple data points
        IrSensor *irStates = new IrSensor[5];
        LineSensor *lineStates = new LineSensor[4];
        EnemyPositions currPosition;
    public:
        WorldState(IrSensor *ir, LineSensor *line);
        EnemyPositions getEnemyPosition();
        bool getIsOnLine();
};

#endif