#include "Robot/algorithm.hpp"

Algorithm::Algorithm(RobotActions* action, Timer* timer) {
  this->action = action;
  this->timer = timer;
  this->line = false;
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
  if (timer->getRunningProcess() == true) { 
    if (timer->getDuration() > 200) {
        action->Backwards(150);
    } else {
      if (algo == pingPongR) {
        action->Right(120);
      } else if (algo == pingPongL) {
        action->Left(120);
      }
    }
    return;
  }

  timer->startTimer(300);

  if (algo == pingPongR) {
    action->Right(120);
  } else if (algo == pingPongL) {
    action->Left(120);
  }
}

void Algorithm::pingPongMove(AlgoLogs algo) {
  if (timer->getRunningProcess() == true && 
      algo == pingPongF) {
      action->Forward(65);
      return;
  }
  timer->startTimer(1);
  action->Forward(65);
}

void Algorithm::backTrack(OnLine line_state, AlgoLogs algo) {
  // The override to other searching algorithms
  // if ((algo != BTBackward || algo != BTFL || algo != BTFR) && timer->getRunningProcess() == true) {
  //   timer->startTimer(300);
  // }

  if (timer->getRunningProcess() == true &&
      (algo == BTBackward || algo == BTFL || algo == BTFR)) {
    if (algo == BTBackward) {
      // This part doesn't work
      // if (timer->getDuration() > 200) {
      //     action->Forward(200);
      // } else {
      //     action->Left(100);
      // }
      // action->Forward(200);
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
  if (!timer->getRunningProcess()) {
    timer->startTimer(750);
    action->Right(150);
    return;
  }

  unsigned long t = timer->getElapsed();

  if (t < 150) {
    action->Right(150);
  } else if (t < 450) {
    action->Left(150);
  } else if (t < 600) {
    action->Right(150);
  } else {
    action->Forward(100);
  }
}

// void Algorithm::Strat2Sweep(bool midDetected) {
//   float currentYaw = *yaw;

//   switch (sweepState) {
//     case SweepInit:
//       action->Right(70);
//       sweepState = SweepWaitEnter;
//       break;

//     case SweepWaitEnter:
//       action->Right(70);

//       if (midDetected) {
//         theta_entry = currentYaw;
//         sweepState = SweepMeasure;
//       }
//       break;

//     case SweepMeasure:
//       action->Right(70);

//       if (!midDetected) {
//         theta_exit = currentYaw;

//         // midpoint angle
//         theta_target = (theta_entry + theta_exit) / 2.0;

//         sweepState = SweepReturn;
//       }
//       break;

//     case SweepReturn: {
//       float error = theta_target - currentYaw;

//       // normalize to [-180, 180]
//       while (error > 180) error -= 360;
//       while (error < -180) error += 360;

//       if (abs(error) < 3) {
//         sweepState = SweepAttack;
//         break;
//       }

//       int turnSpeed = constrain(2.0 * error, -100, 100);

//       if (turnSpeed > 0) {
//         action->Right(turnSpeed);
//       } else {
//         action->Left(-turnSpeed);
//       }
//       break;
//     }

//     case SweepAttack:
//       action->Forward(200);
//       break;
//   }
// }

void Algorithm::SideStrike(EnemyPositions pos, AlgoLogs algo) {
  // TODO: Test this
  // If we are queueing this algo, it will override lines if it does see an
  // enemy but subsequent runs will have to follow line to not fall off
  if (timer->getRunningProcess() == true) {
    if (algo == SideStrikeFL) {
      if (timer->getDuration() > 300) {
        action->Forward(150);
      } else if (timer->getDuration() > 250) {
        action->Left(140);
      } else {
        action->Forward(250);
      }
    } else if (algo == SideStrikeFR) {
      if (timer->getDuration() > 300) {
        action->Forward(150);
      } else if (timer->getDuration() > 250) {
        action->Right(140);
      } else {
        action->Forward(250);
      }
    } else if (algo == SideStrikeL) {
      // EnemyLeft + EnemyRight are going to follow turn to robot before
      // EnemyFL/EnemyFR
      action->Left(160);
    } else if (algo == SideStrikeR) {
      action->Right(160);
    } else {
      action->Forward(70);
    }

    return;
  }
  timer->startTimer(350);
  if (algo == SideStrikeFL) {
    action->Forward(170);
  } else if (algo == SideStrikeFR) {
    action->Forward(170);
  } else if (algo == SideStrikeL) {
    action->Left(140);
  } else if (algo == SideStrikeR) {
    action->Right(140);
  } else {
    action->Forward(70);
  }
}

void Algorithm::evade(EnemyPositions pos) {
  if (timer->getRunningProcess() == true) {
    if (pos == EnemyFL || pos == EnemyLeft) {
      action->ArcRight(150);
    } else if (pos == EnemyFR || pos == EnemyRight) {
      action->ArcLeft(150);
    } else if (pos == EnemyFront) {
      action->Forward(150);
    }
  }

  timer->startTimer(500);
}

bool Algorithm::getTimer() { return timer->getRunningProcess(); }