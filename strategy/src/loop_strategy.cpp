#include <strategy/loop_strategy.h>
#include <iostream>

LoopStrategy::LoopStrategy() {

}

std::vector<int> LoopStrategy::next_action(SensorData input) {
    int output[] = {10, 10};
    return std::vector<int>(output, output + sizeof(output)/sizeof(int));
}