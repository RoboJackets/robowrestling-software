#include <strategy/avoid_strategy.h>
#include <iostream>

AvoidStrategy::AvoidStrategy() {
    state_ = IDLE;
}

std::vector<int> AvoidStrategy::next_action(SensorData input) {
    int output[] = {0, 0};
    state_ = update_state();
    switch (state_) {
    case PUSH:
        output[0] = 70;
        output[1] = 70;
        break;
    case BACK:
        output[0] = -50;
        output[1] = -50;
        break;
    case TURN_LEFT:
        output[0] = -50;
        output[1] = 50;
        break;
    case TURN_RIGHT:
        output[0] = 50;
        output[1] = -50;
        break;
    default:
        break;
    }
    return std::vector<int>(output, output + sizeof(output)/sizeof(int));
}

AvoidStrategy::State AvoidStrategy::update_state() {
    //TODO
}