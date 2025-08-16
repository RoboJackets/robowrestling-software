#ifndef SHAPE_H
#define SHAPE_H

#include "RobotAction.h"
#include "WorldState.h"
#include "algorithms/BackSpinLeft.hpp"
#include "algorithms/BackSpinRight.hpp"

class Shape {
    private:
        BackSpinLeft *backSpinLeft;
        BackSpinRight *backSpinRight;
        RobotAction *robotAction;
        WorldState *worldState;
    public:
        Shape(WorldState *_worldState, RobotAction* _robotAction);
        void Run();
};

#endif