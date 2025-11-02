#include "Robot/algorithm.hpp"

Algorithm::Algorithm(RobotActions *action, Timer *timer) {
    this->action = action;
    this->timer = timer;
}

void Algorithm::RunItDown(EnemyPositions pos) {
    // EnemyPosition only EnemyFront, EnemyFL, EnemyFR
    if (timer->getRunningProcess() == true) {
        action->Attack(pos);
        return;
    }

    // Residual finish out attack
    timer->startTimer(5);
}

void Algorithm::search() {
    action->Circle();
}

void Algorithm::backTrack(OnLine line_state, AlgoLogs algo) {
    if (timer->getRunningProcess() == true) {
        if (algo == BTBackward) {
            if (timer->getDuration() > 5) {
                action->Forward(200);
            } else {
                action->Left(50);
            }
        } else if (algo == BTForward) {
            if (timer->getDuration() > 5) {
                action->Backwards(200);
            } else {
                action->Left(50);
            }
        }
        return;
    }

    // Else start process for line movement
    timer->startTimer(10);
}

bool Algorithm::getTimer() {
    return timer->getRunningProcess();
}