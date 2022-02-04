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
        output[0] = 80;
        output[1] = 80;
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

    return std::vector<int>(output[0], output + sizeof(output)/sizeof(int));
}

// Checks sensors and returns the appropriate state of action
SearchStrat::State SearchStrat::update_state(SensorData input) {
    if () {
        return APPROACH;
    } else if ()
        return TURN_RIGHT;
    } else if () {
        return TURN_LEFT;
    } else {
        return IDLE;
    }
}