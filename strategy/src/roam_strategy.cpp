#include <strategy/roam_strategy.h>
#include <iostream>

RoamStrategy::RoamStrategy() {
    cycle_ = 0;
}

std::vector<int> RoamStrategy::next_action(SensorData input) {
    int output[] = {50, 40};
    if (input.line_buffer_[0] >= 190 || input.line_buffer_[1] >= 190) {
        cycle_ = 1000;
    }
    if (cycle_ > 0) {
        output[0] = -40;
        output[1] = -50;
        cycle_--;
    }
    return std::vector<int>(output, output + sizeof(output)/sizeof(int));
}