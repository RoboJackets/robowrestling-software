#ifndef STATE_STRATEGY_H
#define STATE_STRATEGY_H
#include <strategy/strategy.h>

class StateStrategy: public Strategy {
    public:
        StateStrategy();
        std::vector<int> next_action(SensorData input);

        enum State {

        }

        State state_;
}

#endif