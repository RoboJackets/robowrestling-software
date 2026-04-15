#include "Robot/algorithm.hpp"

Algorithm::Algorithm(RobotActions* action, Timer* timer, float* yaw_ptr) {
  this->action = action;
  this->timer = timer;
  this->line = false;
  this->yaw = yaw_ptr;
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

void Algorithm::RunItDown(EnemyPositions pos, AlgoLogs algo) {
  // The override to other searching algorithms
  if (algo != RunItDownAlgo && timer->getRunningProcess() == true) {
    timer->startTimer(100);
  }

  // EnemyPosition only EnemyFront, EnemyFL, EnemyFR
  if (timer->getRunningProcess() == true) {
    action->Forward(250);
    return;
  }

  // Residual finish out attack
  timer->startTimer(100);
  action->Forward(250);
}

void Algorithm::TurnToEnemy(EnemyPositions pos) {
  if (timer->getRunningProcess() == true) {
    if (pos == EnemyLeft) {
      action->Left(200);
    } else if (pos == EnemyRight) {
      action->Right(200);
    } else if (pos == EnemyFL) {
      action->Left(150);
    } else {
      action->Right(150);
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
  // if (timer->getRunningProcess() == true) {
  //     if (timer->getDuration() > 600) {
  //         action->Left(150);
  //     } else if (timer->getDuration() > 300) {
  //         action->Right(150);
  //     } else {
  //         action->Left(150);
  //     }
  //     return;
  // }
  // timer->startTimer(900);

  if (!timer->getRunningProcess()) {
    timer->startTimer(1100);
    action->Right(150);
    return;
  }

  action->Right(100);
}

void Algorithm::pingPong(OnLine line_state, AlgoLogs algo) {
  if (timer->getRunningProcess() == true &&
      (algo == AlgoLogs::pingPongL || algo == AlgoLogs::pingPongR ||
       algo == AlgoLogs::pingPongF)) {
    if (algo == pingPongR) {
      action->Right(80);
    } else if (algo == pingPongL) {
      action->Left(80);
    } else {
      action->Forward(60);
    }
    return;
  }
  timer->startTimer(300);
  action->Right(80);
}

void Algorithm::backTrack(OnLine line_state, AlgoLogs algo) {
  if (timer->getRunningProcess() == true &&
      (algo == BTBackward || algo == BTFL || algo == BTFR)) {
    if (algo == BTBackward) {
      // This part doesn't work
      // if (timer->getDuration() > 200) {
      //     action->Forward(200);
      // } else {
      //     action->Left(100);
      // }
      action->Forward(200);
    } else if (algo == BTFL || algo == BTFR) {
      if (timer->getDuration() > 250) {
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
  if (!timer->getRunningProcess()) {
    timer->startTimer(1350);
    action->Right(100);
    return;
  }

  unsigned long t = timer->getElapsed();

  if (t < 300) {
    action->Right(125);
  } else if (t < 900) {
    action->Left(125);
  } else if (t < 1200) {
    action->Right(125);
  } else {
    action->Forward(100);
  }
}

void Algorithm::Strat2Sweep(bool midDetected) {
  float currentYaw = *yaw;

  switch (sweepState) {
    case SweepInit:
      action->Right(70);
      sweepState = SweepWaitEnter;
      break;

    case SweepWaitEnter:
      action->Right(70);

      if (midDetected) {
        theta_entry = currentYaw;
        sweepState = SweepMeasure;
      }
      break;

    case SweepMeasure:
      action->Right(70);

      if (!midDetected) {
        theta_exit = currentYaw;

        // midpoint angle
        theta_target = (theta_entry + theta_exit) / 2.0;

        sweepState = SweepReturn;
      }
      break;

    case SweepReturn: {
      float error = theta_target - currentYaw;

      // normalize to [-180, 180]
      while (error > 180) error -= 360;
      while (error < -180) error += 360;

      if (abs(error) < 3) {
        sweepState = SweepAttack;
        break;
      }

      int turnSpeed = constrain(2.0 * error, -100, 100);

      if (turnSpeed > 0) {
        action->Right(turnSpeed);
      } else {
        action->Left(-turnSpeed);
      }
      break;
    }

    case SweepAttack:
      action->Forward(200);
      break;
  }
}

void Algorithm::SideStrike(EnemyPositions pos) {
  // TODO: Test this
  // If we are queueing this algo, it will override lines if it does see an
  // enemy but subsequent runs will have to follow line to not fall off
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
      // EnemyLeft + EnemyRight are going to follow turn to robot before
      // EnemyFL/EnemyFR
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

void Algorithm::evade() {
  int v = random(0, 2);
  if (v == 0) {
    action->ArcLeft(200);
  } else {
    action->ArcRight(200);
  }
}

bool Algorithm::getTimer() { return timer->getRunningProcess(); }