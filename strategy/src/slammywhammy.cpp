#include <strategy/slammywhammy.h>
#include <iostream>

SlammyWhammy::SlammyWhammy() {
    state_ = 0;
}

std::vector<int> SlammyWhammy::next_action(SensorData input) {
    int output[] = {0, 0};
    return std::vector<int>(output, output + sizeof(output)/sizeof(int));
}