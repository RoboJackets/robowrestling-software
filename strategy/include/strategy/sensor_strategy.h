#include <strategy/strategy.h>

class SensorStrategy: public Strategy {
    public:
        SensorStrategy();
        std::vector<int> next_action(LineBuffer l, ImuData i);
        int state_;
};