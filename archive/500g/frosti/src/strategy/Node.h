#ifndef NODE_H
#define NODE_H

#include "../Vector2.h"
#include "../RobotState.h"

class Node {
    private:
    public:
        virtual Vector2<double> strategy(RobotState robotState);
};

#endif