#include "Robot/algorithm.hpp"

Algorithm::Algorithm(RobotActions *action) {
    this->action = action;
}
void Algorithm::RunItDown() {
    action->Forward();
}

