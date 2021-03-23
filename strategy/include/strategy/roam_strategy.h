#ifndef ROAM_STRATEGY_H
#define ROAM_STRATEGY_H
#include <strategy/strategy.h>

class RoamStrategy: public Strategy {
    public:
        RoamStrategy();
        std::vector<int> next_action(LineBuffer lines);
        int cycle_;
        bool check_lines(LineBuffer lines);
};

#endif