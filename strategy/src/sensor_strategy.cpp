#include <strategy/sensor_strategy.h>


SensorStrategy::SensorStrategy() {
}

std::vector<int> SensorStrategy::next_action(SensorData input) {
    int output[] = {100,0};
    for (int b : input.line_buffer_) {
        if (b >= 190) {
            if (input.z_gyro_ <= 0) {
                output[0] = 0;
                output[1] = 100;
            } else {
                output[0] = 100;
                output[0] = 0;
            }
        }
    } 
    for (int d : input.dist_buffer_) {
       if (d < 100) {
           output[0] = 100;
           output[1] = 100;
       } 
    }
    return std::vector<int>(output, output + sizeof(output)/sizeof(int));
}

