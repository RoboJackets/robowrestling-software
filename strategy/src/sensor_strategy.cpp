#include <strategy/sensor_strategy.h>

SensorStrategy::SensorStrategy() {
    state_ = 0;
}

std::vector<int> SensorStrategy::next_action(std::vector<double> inputs) {
    int output[] = {50, 100};
    return std::vector<int>(output, output + sizeof(output)/sizeof(int));
}