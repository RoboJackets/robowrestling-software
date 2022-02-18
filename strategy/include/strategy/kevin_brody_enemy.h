#ifndef KEVIN_BRODY_ENEMY_H
#define KEVIN_BRODY_ENEMY_H
#include <strategy/strategy.h> 

class KevinBrodyStrategyEnemy: public Strategy {
    public:
        KevinBrodyStrategyEnemy();
        std::vector<int> next_action(SensorData input);

        enum State {
            IDLE,
            FORWARD,
            BACK,
            TURN_LEFT,
            TURN_RIGHT,
            LEFT_BACK,
            RIGHT_BACK,
            STOP,
            SEARCH
        };
        State state;
        State update_state(SensorData input);
};

#endif
