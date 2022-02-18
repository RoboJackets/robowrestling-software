#ifndef KEVIN_BRODY_H
#define KEVIN_BRODY_H
#include <strategy/strategy.h> 

class KevinBrodyStrategy: public Strategy {
    public:
        KevinBrodyStrategy();
        std::vector<int> next_action(SensorData input);

        enum State {
            IDLE,
            FORWARD,
            BACK,
            TURN_LEFT,
            TURN_RIGHT,
            STOP,
            SEARCH
        };
        State state;
        State update_state(SensorData input);
};

#endif
