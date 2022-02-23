#ifndef STATE_STRATEGY_H
#define STATE_STRATEGY_H
#include <strategy/strategy.h>
#include <iostream>
#define MAX_DIST 150

class StateStrategy: public Strategy {
    public:
        enum State {
            SEARCH,
            TURN_LEFT,
            TURN_RIGHT,
            FORWARD,
            STOP
        };

        StateStrategy();
        std::vector<int> next_action(SensorData input);
        void update_state(SensorData input);

        State state_;
};

#endif
