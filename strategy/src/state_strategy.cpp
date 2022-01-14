#include "strategy/state_strategy.h"

StateStrategy::StateStrategy() {
    state_ = SEARCH;
}

void StateStrategy::update_state(SensorData input) {
    state_ = SEARCH;
    auto hit_far_l = input.dist_buffer_[0] < MAX_DIST && input.dist_buffer_[0] > 0;
    auto hit_mid_l = input.dist_buffer_[1] > 0 && input.dist_buffer_[1] < MAX_DIST;
    auto hit_c_l = input.dist_buffer_[2] > 0 && input.dist_buffer_[2] < MAX_DIST;
    auto hit_c_r = input.dist_buffer_[3] > 0 && input.dist_buffer_[3] < MAX_DIST;
    auto hit_mid_r = input.dist_buffer_[4] > 0 && input.dist_buffer_[4] < MAX_DIST;
    auto hit_far_r = input.dist_buffer_[5] > 0 && input.dist_buffer_[5] < MAX_DIST;
    auto on_line = input.line_buffer_[0] == 0 || input.line_buffer_[1] == 0;

    if ((hit_c_r || hit_c_l)) {
        state_ = FORWARD;
        std::cout << "forward" << std::endl; 
    } else if (hit_far_l || hit_mid_l) {
        state_ = TURN_LEFT;
        std::cout << "left" << std::endl; 
    } else if (hit_far_r || hit_mid_r) {
        state_ = TURN_RIGHT;
        std::cout << "right" << std::endl; 
    }

    if (on_line) {
        state_ = STOP;
    }
}

std::vector<int> StateStrategy::next_action(SensorData input) {
    update_state(input);
    int output[] = {0, 0};

    switch(state_) {
        case FORWARD:
            output[0] = 75;
            output[1] = 75;
            break;
        case TURN_LEFT:
            output[0] = 75;
            output[1] = 0;
            break;
        case TURN_RIGHT:
            output[0] = 0;
            output[1] = 75;
            break;
        case STOP:
            output[0] = -50;
            output[1] = -50;
            break;
        default:
            output[0] = -50;
            output[1] = 50;
            break;
    }

    return std::vector<int>(output, output + sizeof(output)/sizeof(int));
}