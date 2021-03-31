#include <strategy/avoid_strategy.h>
#include <iostream>

AvoidStrategy::AvoidStrategy() {
    state_ = IDLE;
}

std::vector<int> AvoidStrategy::next_action(SensorData input) {
    int output[] = {0, 0};
    state_ = update_state(input);
    switch (state_) {
    case PUSH:
        output[0] = 70;
        output[1] = 70;
        break;
    case BACK:
        output[0] = -40;
        output[1] = -40;
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

AvoidStrategy::State AvoidStrategy::update_state(SensorData input) {
    if (input.dist_buffer_[2] < 30 || input.dist_buffer_[3] < 30) {
        return PUSH;
    } else if (input.dist_buffer_[2] < 150 || input.dist_buffer_[3] < 150) {
        return TURN_LEFT;
    } else if ((input.line_buffer_[1] > 190 || input.line_buffer_[1] > 190)
        && (input.dist_buffer_[0] < 150 || input.dist_buffer_[1] < 150)
        && (input.dist_buffer_[4] < 150 || input.dist_buffer_[5] < 150)) {
        return BACK;
    } else {
        return TURN_RIGHT;
    }
}