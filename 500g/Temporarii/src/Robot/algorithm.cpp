#include "Robot/algorithm.hpp"

Algorithm::Algorithm(RobotActions *action, Timer *timer) {
    this->action = action;
    this->timer = timer;
}

void Algorithm::Test() {
    if (timer->getRunningProcess() == true) {
        if (timer->getDuration() > 4000) {
            action->Forward(60);
        } else if (timer->getDuration() > 2000) {
            action->Left(60);
        } else {
            action->Right(60);
        }
        return;
    }
    timer->startTimer(4500);
    action->Forward(60);
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
        if (pos == EnemyLeft) {
            action->Right(200);
        } else if (pos == EnemyRight) {
            action->Left(200);
        } else if (pos == EnemyFL) {
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
    if (timer->getRunningProcess() == true) {
        if (timer->getDuration() > 853) {
            action->Left(70);
        } else if (timer->getDuration() > 300) {
            action->Right(70);
        } else {
            action->Left(70);
        }
        return;
    }
    timer->startTimer(1153);
}

void Algorithm::backTrack(OnLine line_state, AlgoLogs algo) {
    if (timer->getRunningProcess() == true) {
        if (algo == BTBackward) {
            // This part doesn't work
            // if (timer->getDuration() > 200) {
            //     action->Forward(200);
            // } else {
            //     action->Left(100);
            // }
        } else if (algo == BTFL || algo == BTFR) {
            if (timer->getDuration() > 200) {
                action->Backwards(200);
            } else {
                if (algo == BTFL) {
                    action->Right(130);
                } else {
                    action->Left(130);
                }
            }
        }
        return;
    }

    // Else start process for line movement
    timer->startTimer(300);
    if (algo == BTBackward) {
        action->Forward(200);
    } else if (algo == BTFR || algo == BTFL) {
        action->Backwards(200);
    }
}

void Algorithm::fryThem() {
    if (timer->getRunningProcess() == true) {
        // 161 Right
        if (timer->getDuration() > 689) {
            action->Right(100);
        } else if (timer->getDuration() > 639) {
            // 50 Wait
            action->Right(0);
        }  else if (timer->getDuration() > 350) {
            // 289 Left
            action->Left(100);
        } else if (timer->getDuration() > 300) {
            // 50 Wait
            action->Left(0);
        } else if (timer->getDuration() > 150) {
            // 150 Right
            action->Right(100);
        } else if (timer->getDuration() > 100) {
            // 50 Wait
            action->Right(0);
        } else {
            // 100 Forward
            action->Forward(70);
        }
        return;
    }
    timer->startTimer(850);
    action->Right(100);
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