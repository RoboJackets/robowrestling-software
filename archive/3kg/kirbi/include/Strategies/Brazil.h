#ifndef BRAZIL_H
#define BRAZIL_H

#define BRAZIL_TURN_MILLIS 650

#include <Arduino.h>
#include "Strategies/Behaviors/Nodes/Node.h"
#include "Robot/RobotState.h"

class Brazil : public BT::Node<RobotState, RobotState> {
public:
    Brazil(int speed);

    RobotState Run(RobotState state);

private:
    int _speed;
    int _turnStartMillis;
    bool _hasHitEdge;
};

#endif
