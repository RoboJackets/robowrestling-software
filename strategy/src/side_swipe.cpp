#include <strategy/side_swipe.h>

SideSwipe::SideSwipe() {
    mState = IDLE;
}

std::vector<int> SideSwipe::next_action(SensorData input) {
    int output[] = {100,-100};


    return std::vector<int>(output, output + sizeof(output)/sizeof(int));
}


SideSwipe::State SideSwipe::updateState(SensorData input) {
    return IDLE; 
}