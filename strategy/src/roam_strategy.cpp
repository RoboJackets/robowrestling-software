#include <strategy/roam_strategy.h>
#include <iostream>

RoamStrategy::RoamStrategy() {
    cycle_ = 0;
}

std::vector<int> RoamStrategy::next_action(LineBuffer lines) {
    int output[] = {60, 40};
    if (check_lines(lines)) {
        output[0] = -50;
        output[1] = 0;
        cycle_ = 10;
    }
    if (cycle_ > 0) {
        output[0] = -50;
        output[1] = 0;
        cycle_--;
    }
    return std::vector<int>(output, output + sizeof(output)/sizeof(int));
}

bool check_lines(LineBuffer lines) {
    for (int l: lines.buffer) {
        if (l >= 190) return true;
    }
    return false;
}