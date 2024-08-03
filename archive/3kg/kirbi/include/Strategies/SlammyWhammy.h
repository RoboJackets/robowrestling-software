#ifndef SLAMMY_WHAMMY_H
#define SLAMMY_WHAMMY_H

#include <Arduino.h>
#include "Robot/RobotState.h"
#include "Strategies/Behaviors/Nodes/SequenceNode.h"
#include "Strategies/Behaviors/Nodes/Node.h"
#include "Strategies/Behaviors/Search.h"
#include "Strategies/Behaviors/Slam.h"

#define LOCKOUT_TIME 300

class SlammyWhammy : public BT::Node<RobotState, RobotState> {
public:
    SlammyWhammy(int turnSpeed, int slamSpeed);

    RobotState Run(RobotState state);

private:
    Search* search;
    Slam* slam;
    unsigned int lockout = 0;
};

#endif
