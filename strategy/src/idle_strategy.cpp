#include <strategy/idle_strategy.h>
#include <iostream>

IdleStrategy::IdleStrategy() {
    
}

std::vector<int> IdleStrategy::next_action(SensorData input) {
    int output[] = {0, 0};
    return std::vector<int>(output, output + sizeof(output)/sizeof(int));
}