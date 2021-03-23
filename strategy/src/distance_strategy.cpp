#include <iostream>
#include <strategy/distance_strategy.h>

DistanceStrat::DistanceStrat() {
    state_ = State.IDLE;
}

std::vector<int> DistanceStrat::next_action(SensorData input) {
    return std::vector<int>(2, 90);
}