#ifndef LOOP_STRATEGY_H
#define LOOP_STRATEGY_H
#include <strategy/strategy.h>

class LoopStrategy: public Strategy {
    public:
        LoopStrategy();
        std::vector<int> next_action(SensorData input);
};

#endif
