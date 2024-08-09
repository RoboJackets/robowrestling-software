#ifndef SEARCH_H
#define SEARCH_H

#include "Robot/RobotState.h"
#include "Strategies/Behaviors/Nodes/Node.h"

class Search : public BT::Node<RobotState, RobotState> {
public:
    enum State {
        SEARCH,
        TURN_LEFT,
        TURN_RIGHT
    };

    Search(int turnSpeed);

    RobotState Run(RobotState inputs) override;

    void updateState(RobotState inputs);

protected:
    int turnSpeed;
    State state;
};

#endif
