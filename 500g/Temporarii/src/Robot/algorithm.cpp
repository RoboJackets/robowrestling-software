#include "Robot/algorithm.hpp"

Algorithm::Algorithm(RobotActions *action, Timer *timer) {
    this->action = action;
    this->timer = timer;
}

void Algorithm::RunItDown(EnemyPositions pos) {
    // Modify this for timer checks
    action->Attack(pos);
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
   // TODO: Implement timer control with backTracking

    if (line_state == LineBL) {
        action->Forward(40);
    } else if (line_state == LineBR) {
        action->Forward(40);
    } else if (line_state == LineFL) {
        action->Backwards(40);
    } else if (line_state == LineFR) {
        action->Backwards(40);
    }

    // Otherwise, LineNone
}