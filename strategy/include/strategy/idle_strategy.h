#ifndef IDLE_STRATEGY_H
#define IDLE_STRATEGY_H
#include <strategy/strategy.h>

class IdleStrategy: public Strategy {
    public:
        IdleStrategy();
        std::vector<int> next_action(SensorData input);
};

#endif
