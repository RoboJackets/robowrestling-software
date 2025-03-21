#include <Sensors/irSensor.h>
#include <Sensors/lineSensor.h>
#include "Sensors/WorldState.hpp"

WorldState::WorldState(IrSensor *ir[5], LineSensor *line[4])
{
    for (int i = 0; i < 5; i++)
    {
        irStates[i] = ir[i];
    }
    for (int i = 0; i < 4; i++)
    {
        lineStates[i] = line[i];
    }
    currPosition = NoOp;
}

WorldState::WorldState()
{
    currPosition = NoOp;
}

/*IrSensor WorldState::getIRState() {
    return irStates;
}
*/
EnemyPositions WorldState::getEnemyPosition()
{
    // IrSensor Array = {Left, MidLeft, Mid, MidRight, Right}
    // Middle pins all on is full Sends
    if (irStates[1]->getValue() == 1 && irStates[2]->getValue() == 1 && irStates[3]->getValue() == 1)
    {
        currPosition = SEND;
        return SEND;
    }
    if (irStates[0]->getValue() == 1)
    {
        currPosition = Left;
        return Left;
    }
    if (irStates[1]->getValue() == 1)
    {
        currPosition = MidL;
        return MidL;
    }
    if (irStates[2]->getValue() == 1)
    {
        currPosition = Mid;
        return Mid;
    }
    if (irStates[3]->getValue() == 1)
    {
        currPosition = MidR;
        return MidR;
    }
    if (irStates[4]->getValue() == 1)
    {
        currPosition = Right;
        return Right;
    }
    currPosition = NoOp;
    return NoOp;
}

OnLine WorldState::getIsOnLine()
{
    int length = sizeof(lineStates) / sizeof(lineStates[0]);
    for (int i = 0; i < length; i++)
    {
        // Detecting white (the line)
        if (lineStates[i]->getValue() >= 700)
        {
            return on_line;
        }
    }
    return not_on_line;
}
