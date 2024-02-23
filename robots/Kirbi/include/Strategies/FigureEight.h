#ifndef FIGURE_EIGHT
#define FIGURE_EIGHT

#include <Arduino.h>
#include "Robot/RobotState.h"
#include "Strategies/Behaviors/Nodes/Node.h"

class FigureEight : public BT::Node<RobotState, RobotState> {
public:
    FigureEight(int speed, int time2Switch);


    RobotState Run(RobotState state);

private:
    int _speed = 0;
    uint32_t _time2Switch;
    uint32_t _lastTime = 0;
    bool dir = true;  // true -> right, false -> left
};

#endif
