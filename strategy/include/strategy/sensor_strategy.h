#include <strategy/strategy.h>


class SensorStrategy: public Strategy {
    public:
        SensorStrategy();
        std::vector<int> next_action(DistanceBuffer d, LineBuffer l, EncoderBuffer e, ImuData i);
        int state_;
};