#include <strategy/strategy.h>

class SensorStrategy: public Strategy {
    public:
        SensorStrategy();
        std::vector<int> next_action(std::vector<double> inputs);
        int state_;
};