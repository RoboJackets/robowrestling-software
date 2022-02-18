#include <opening/no_opening.h>
#include <iostream>

NoOpening::NoOpening() {
    done = true;
}

std::vector<int> NoOpening::execute(SensorData input) {
    int output[] = {0, 0};
    
    return std::vector<int>(output, output + sizeof(output) / sizeof(int));
}
