#include "Robot/algorithm.hpp"

Algorithm::Algorithm(RobotActions *action, Timer *timer) {
    this->action = action;
    this->timer = timer;
}

void Algorithm::RunItDown(EnemyPositions pos) {
    // EnemyPosition only EnemyFront, EnemyFL, EnemyFR
    if (timer->getRunningProcess() == true) {
        action->Forward(250);
        return;
    }

    // Residual finish out attack
    timer->startTimer(50);
    action->Forward(250);
}

void Algorithm::TurnToEnemy(EnemyPositions pos) {
    if (timer->getRunningProcess() == true) {
        if (pos == EnemyLeft || pos == EnemyFL) {
            action->Right(150);
        } else {
            action->Left(150);
        }
        return;
    }

    timer->startTimer(250);
    if (pos == EnemyLeft || pos == EnemyFL) {
        action->Right(150);
    } else {
        action->Left(150);
    }
}

void Algorithm::search() {
    action->Circle();
}

void Algorithm::backTrack(OnLine line_state, AlgoLogs algo) {
    if (timer->getRunningProcess() == true) {
        if (algo == BTBackward) {
            if (timer->getDuration() > 200) {
                action->Forward(200);
            } else {
                action->Left(150);
            }
        } else if (algo == BTForward) {
            if (timer->getDuration() > 500) {
                action->Backwards(200);
            } else {
                action->Left(150);
            }
        }
        return;
    }

    // Else start process for line movement
    timer->startTimer(300);
    if (algo == BTBackward) {
        action->Forward(200);
    } else if (algo == BTForward) {
        action->Backwards(200);
    }
}

void Algorithm::fryThem() {
    if (timer->getRunningProcess() == true) {
        if (timer->getDuration() > 1800) {
            action->Left(120);
        } else if (timer->getDuration() > 1400) {
            action->Right(120);
        } else if (timer->getDuration() > 1200) {
            action->Left(120);
        } else {
            action->Forward(70);
        }
        return;
    }
    timer->startTimer(2000);
    action->Left(120);
}

void Algorithm::SideStrike(EnemyPositions pos) {
    // TODO: Test this
    // If we are queueing this algo, it will override lines if it does see an enemy
    // but subsequent runs will have to follow line to not fall off
    if (timer->getRunningProcess() == true) {
        if (pos == EnemyFL) {
            if (timer->getDuration() > 1500) {
                action->Forward(200);
            } else if (timer->getDuration() > 1400) {
                action->Left(200);
            } else {
                action->Forward(200);
            }
        } else if (pos == EnemyFR) {
            if (timer->getDuration() > 1500) {
                action->Forward(200);
            } else if (timer->getDuration() > 1400) {
                action->Right(200);
            } else {
                action->Forward(200);
            }
        } else if (pos == EnemyLeft) {
            // EnemyLeft + EnemyRight are going to follow turn to robot before EnemyFL/EnemyFR
            action->Left(150);
        } else if (pos == EnemyRight) {
            action->Right(150);
        }
        return;
    }
    timer->startTimer(2000);
    if (pos == EnemyFL) {
        action->Forward(200);
    } else if (pos == EnemyFR) {
        action->Forward(200);
    } else if (pos == EnemyLeft) {
        action->Left(150);
    } else if (pos == EnemyRight) {
        action->Right(150);
    }
}

bool Algorithm::getTimer() {
    return timer->getRunningProcess();
}