#include <strategy/loop_strategy.h>
#include <iostream>

LoopStrategy::LoopStrategy() {
    //Always face tangent to clockwise in the arena at 1 meter from center
}

std::vector<int> LoopStrategy::next_action(SensorData input) {
    int output[] = {30,30};
    return std::vector<int>(output, output + sizeof(output)/sizeof(int));
}