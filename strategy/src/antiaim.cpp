#include <strategy/antiaim.h>
#include <iostream>

AntiAim::AntiAim() {
    state = SPIN;
}

// remember to use IMU sensor somehow
std::vector<int> AntiAim::next_action(SensorData input) {
    int output[] = {0, 0};
    state = update_state(input);
    switch (state) {
    case STOP:
        output[0] = 0;
        output[1] = 0;
        break;
    // turns in place
    case SPIN:
        output[0] = -50;
        output[1] = 50;
        break;
    default:
        break;
    }

    return std::vector<int>(output, output + sizeof(output)/sizeof(int));
}

AntiAim::State AntiAim::update_state(SensorData input) {
    
    return SPIN;

}
