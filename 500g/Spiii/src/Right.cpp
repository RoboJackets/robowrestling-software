#include "Right.hpp"

Right::Right(WorldState* _worldState, RobotAction* _robotAction) {
    worldState = _worldState;
    robotAction = _robotAction;
    left_turn_timer = new Timer(LEFT_TURN_TIMER_DURATION);
    right_turn_timer = new Timer(RIGHT_TURN_TIMER_DURATION);
    final_spin_timer = new Timer(FINAL_SPIN_TIMER_DURATION);
    start_flag = true;
}

bool Right::run() {
    if (start_flag) {
        left_turn_timer->resetTimer();
        right_turn_timer->resetTimer();
        final_spin_timer->resetTimer();
        start_flag = false;
    }
    if (!left_turn_timer->isReady()) {
        robotAction->spinRight(MAX_SPEED);
    }
    else if (!right_turn_timer->isReady()) {
        robotAction->turn(MOD, MAX_SPEED);
    }
    else if (!final_spin_timer->isReady()) {
        robotAction->spinLeft(MAX_SPEED);
    } else {
        return true;
    }
    return false;
}