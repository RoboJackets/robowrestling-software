#include "Robot/algorithm.hpp"

Algorithm::Algorithm(RobotActions *action) {
    this->action = action;
}

void Algorithm::RunItDown() {
    action->Forward();
}

void Algorithm::search() {
    action->Circle();
}

void Algorithm::backTrack(OnLine line_state) {
    // TODO: Modify this to include proper line movement
    /* Example: When left front line sensor is on line, what does that mean?
    * When left_on_line or right_on_line, make the robot move forward (You are in push battle)
    * Front_on_line means you have pushed over line, rotate and scan
    */
    if (line_state == left_front_on_line) {
        action->Circle();
    } else if (line_state == right_front_on_line) {
        action->Circle();
    } else if (line_state == left_on_line) {
        action->Forward();
    } else {
        action->Forward();
    }
}