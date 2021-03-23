#include <strategy/sensor_strategy.h>


SensorStrategy::SensorStrategy() {
    state_ = 0;
}

std::vector<int> SensorStrategy::next_action(DistanceBuffer d, LineBuffer l, EncoderBuffer e, ImuData i) {
    std::vector<int> ret;
    for (int i : l.buffer) {
        if (i == 255) {
            ret = {25, 0};
        }
    }
    
    return ret;
}

