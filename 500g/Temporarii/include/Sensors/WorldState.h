#include "Sensors/irSensor.cpp"
#include "Sensors/lineSensor.cpp"
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
        char irStates[5] = {"Mid", "MidL", "MidR", "Left", "Right"};
        char lineStates[4] = {};
    public:
        int getEnemyPosition(IrSensor value);
        int getIsOnLine(LineSensor value);
};

#endif