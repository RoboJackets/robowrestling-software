#include <strategy/kevin_brody.h>
#include <iostream>

KevinBrodyStrategy::KevinBrodyStrategy() {
    state = IDLE;
}

// remember to use IMU sensor somehow
std::vector<int> KevinBrodyStrategy::next_action(SensorData input) {
    int output[] = {0, 0};
    state = update_state(input);
    switch (state) {
    case FORWARD:
        output[0] = 100;
        output[1] = 100;
        break;
    case BACK:
        output[0] = -100;
        output[1] = -100;
        break;
    case TURN_LEFT:
        output[0] = 0;
        output[1] = 100;
        break;
    case TURN_RIGHT:
        output[0] = 100;
        output[1] = 0;
        break;
    case STOP:
        output[0] = 0;
        output[1] = 0;
        break;
    case SEARCH:
        output[0] = 50;
        output[1] = -50;
        break;
    default:
        break;
    }

    return std::vector<int>(output, output + sizeof(output)/sizeof(int));
}

KevinBrodyStrategy::State KevinBrodyStrategy::update_state(SensorData input) {
    // if (input.dist_buffer_[2] < 30 || input.dist_buffer_[3] < 30) { //front ones
    //     return FORWARD;
    // } else if (input.dist_buffer_[2] < 150 || input.dist_buffer_[3] < 150) {
    //     return TURN_LEFT;
    // } else if ((input.line_buffer_[1] > 190 || input.line_buffer_[1] > 190)
    //     && (input.dist_buffer_[0] < 150 || input.dist_buffer_[1] < 150) // left
    //     && (input.dist_buffer_[4] < 150 || input.dist_buffer_[5] < 150)) { // right
    //     return BACK;
    // } else {
    //     return TURN_RIGHT;
    // }
    return FORWARD;
}