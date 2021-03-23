#include <strategy/sensor_strategy.h>


SensorStrategy::SensorStrategy() {
    state_ = 0;
}

std::vector<int> SensorStrategy::next_action(SensorData input) {
    int output[] = {50,50};
    for (int b : l.buffer) {
        if (b == 255) {
            if (i.z_gyro_ <= 0) {
                output[0] = 0;
                output[1] = 50;
            } else {
                output[0] = 50;
                output[0] = 0;
            }
        }
    } 
    return std::vector<int>(output, output + sizeof(output)/sizeof(int));
}

