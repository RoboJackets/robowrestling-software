#ifndef AVOID_STRATEGY_H
#define AVOID_STRATEGY_H
#include <strategy/strategy.h>

class AvoidStrategy: public Strategy {
    public:
        AvoidStrategy();
        std::vector<int> next_action(LineBuffer lines, DistanceBuffer dists);

        enum State {
            IDLE,
            PUSH,
            BACK,
            TURN_LEFT,
            TURN_RIGHT
        };

        State state_;
        State update_state();
};

#endif