#include <strategy/search_strategy.h>
#include <iostream>

// Create and initialize data needed for the strategy
SearchStrat::SearchStrat() {
    state = IDLE;
}

// Returns the intended action in the format {Left Motor Power %, Right Motor Power %}
std::vector<int> SearchStrat::next_action(SensorData input) {
    int output[] = {0, 0};
    state = update_state(input);

    switch (state) {
    case IDLE:
        output[0] = 0;
        output[1] = 0;
        break;
    
    case APPROACH:
        output[0] = 30;
        output[1] = 30;
        break;
    case TURN_LEFT:
        output[0] = 50;
        output[1] = -50;
        break;
    case TURN_RIGHT:
        output[0] = -50;
        output[1] = 50;
        break;
    case BACK:
        output[0] = -1;
        output[1] = -1;

    default:
        break;
    }

    return std::vector<int>(output, output + sizeof(output)/sizeof(int));
}

// Checks sensors and returns the appropriate state of action
SearchStrat::State SearchStrat::update_state(SensorData input) {
    if ((input.line_buffer_[0] > 0 || input.line_buffer_[1] > 0)) {
        std::cout << "Line Sensor Hit\n";
        return BACK;
    }
    else if ((input.line_buffer_[2] > 180 || input.line_buffer_[3] > 180)) {
        return BACK;
    } else if (input.dist_buffer_[4] < 75 || input.dist_buffer_[5] < 75) {
        return TURN_RIGHT;
    } else if (input.dist_buffer_[0] < 75 || input.dist_buffer_[1] < 75) {
        return TURN_LEFT;
    } else  if (input.dist_buffer_[2] < 20 || input.dist_buffer_[3] < 20) {
        return APPROACH;
    } else {
        return APPROACH;
    }
}