#ifndef SHAPE_H
#define SHAPE_H

#include "RobotAction.h"
#include "WorldState.h"
#include "BackSpin.hpp"

class Shape {
    private:
        BackSpin *backSpinLeft;
        BackSpin *backSpinRight;
        Action *previousAction;
        RobotAction *robotAction;
        WorldState *worldState;
    public:
        Shape(WorldState *_worldState, RobotAction* _robotAction);
        void run();
};

#endif