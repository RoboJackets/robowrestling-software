#include <strategy/strategy.h>

class SensorStrategy: public Strategy {
    public:
        SensorStrategy();
        std::vector<int> next_action(SensorData input);
        int state_;
};