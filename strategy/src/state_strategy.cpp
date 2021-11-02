#include "strategy/state_strategy.h"

StateStrategy::StateStrategy() {
    state_ = SEARCH;
}

void StateStrategy::update_state(SensorData input) {
    state_ = SEARCH;
    auto hit_far_l = input.dist_buffer_[0] > 0;
    auto hit_mid_l = input.dist_buffer_[1] > 0;
    auto hit_c_l = input.dist_buffer_[2] > 0;
    auto hit_c_r = input.dist_buffer_[3] > 0;
    auto hit_mid_r = input.dist_buffer_[4] > 0;
    auto hit_far_r = input.dist_buffer_[5] > 0;
    auto on_line = input.line_buffer_[0] > 0 || input.line_buffer_[1] > 0;

    if ((hit_c_r && hit_c_l) || on_line) {
        state_ = FORWARD;
    } else if (hit_far_l || hit_mid_l) {
        state_ = TURN_LEFT;
    } else if (hit_far_r || hit_mid_r) {
        state_ = TURN_RIGHT;
    }
}

std::vector<int> StateStrategy::next_action() {
    std::vector<int> ret = std::vector<int>(2, 0);

    switch(state_) {
        case FORWARD:
            ret[0] = 100;
            ret[1] = 100;
            break;
        case TURN_LEFT:
            ret[0] = 100;
            ret[1] = 0;
            break;
        case TURN_RIGHT:
            ret[0] = 0;
            ret[1] = 100;
            break;
        default:
            ret[0] = 50;
            ret[1] = -50;
            break;
    }

    return ret;

}