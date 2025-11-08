#include "Robot/algorithm.hpp"

Algorithm::Algorithm(RobotActions *action, Timer *timer) {
    this->action = action;
    this->timer = timer;
}

void Algorithm::RunItDown(EnemyPositions pos) {
    // EnemyPosition only EnemyFront, EnemyFL, EnemyFR
    if (timer->getRunningProcess() == true) {
        action->Forward(200);
        return;
    }

    // Residual finish out attack
    timer->startTimer(5);
    action->Forward(200);
}

void Algorithm::TurnToEnemy(EnemyPositions pos) {
    if (timer->getRunningProcess() == true) {
        if (pos == EnemyLeft || pos == EnemyFL) {
            action->Right(100);
        } else {
            action->Left(100);
        }
        return;
    }

    timer->startTimer(500);
    if (pos == EnemyLeft || pos == EnemyFL) {
        action->Right(100);
    } else {
        action->Left(100);
    }
}

void Algorithm::search() {
    action->Circle();
}

void Algorithm::backTrack(OnLine line_state, AlgoLogs algo) {
    if (timer->getRunningProcess() == true) {
        if (algo == BTBackward) {
            if (timer->getDuration() > 500) {
                action->Forward(100);
            } else {
                action->Left(70);
            }
        } else if (algo == BTForward) {
            if (timer->getDuration() > 500) {
                action->Backwards(100);
            } else {
                action->Left(70);
            }
        }
        return;
    }

    // Else start process for line movement
    timer->startTimer(800);
    if (algo == BTBackward) {
        action->Forward(100);
    } else if (algo == BTForward) {
        action->Backwards(100);
    }
}

void Algorithm::fryThem() {
    if (timer->getRunningProcess() == true) {
        if (timer->getDuration() > 1600) {
            action->Left(90);
        } else if (timer->getDuration() > 800) {
            action->Right(90);
        } else if (timer->getDuration() > 400) {
            action->Left(90);
        } else {
            action->Forward(100);
        }
        return;
    }
    timer->startTimer(2000);
    action->Left(90);
}

bool Algorithm::getTimer() {
    return timer->getRunningProcess();
}