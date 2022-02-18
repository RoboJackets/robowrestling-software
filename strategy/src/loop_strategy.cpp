#include <strategy/loop_strategy.h>
#include <iostream>

// supposed to go in a nice circle. does not do it.
LoopStrategy::LoopStrategy() {
    //Always face tangent to clockwise in the arena at .5 meter from center
}

std::vector<int> LoopStrategy::next_action(SensorData input) {
    // vector is left and right motor strength
    int output[] = {50,33};
    return std::vector<int>(output, output + sizeof(output)/sizeof(int));
}