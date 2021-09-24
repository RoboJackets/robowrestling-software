#include <strategy/idle_strategy.h>
#include <iostream>

IdleStrategy::IdleStrategy() {
    
}

std::vector<int> IdleStrategy::next_action(SensorData input) {
    int output[] = {80, 80};
    return std::vector<int>(output, output + sizeof(output)/sizeof(int));
}