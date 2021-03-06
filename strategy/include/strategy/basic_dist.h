#ifndef basic_dist_h
#define basic_dist_h
#include <strategy/strategy.h>

class BasicDist: public Strategy {
    public:
        BasicDist();
        std::vector<int> next_action(std::vector<double> inputs);
};

#endif //basic_dist_h