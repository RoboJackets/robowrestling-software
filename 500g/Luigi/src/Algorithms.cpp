#include "Algorithms.hpp"
#include "enums.hpp"
#include <Arduino.h>

algorithms::algorithms(motor_actions* motors, world_state* world, timer* last_state_changed, timer* behavior_timer) {
  this->motors = motors;
  this->world = world;
  this->last_state_changed = last_state_changed;
  this->behavior_timer = behavior_timer;
}

void algorithms::selectMode() {
  EnemyPosition e = world->enemy_pos();
  if(currentEnemyPos != e && currentEnemyPos != NONE) {
    lastEnemyPos = currentEnemyPos;
    last_state_changed->reset();
    last_state_changed->start();
  }
  currentEnemyPos = e;
  LinePosition linePos = world->line_check();

  chooseAction(currentEnemyPos, linePos);
}

void algorithms::followBehavior() {
  if (behavior_timer->isFinished()) {
    behavior = NO;
  }
  else {
    switch (behavior) {
      case TURN_AROUND:
        if (behavior_timer->elapsedMilliseconds() < 250) {
          motors->driveBackward(200);
        }
        else {
          motors->spinRight(100);
        }
        break;
      default:
        break;
    }
  }
}

void algorithms::chooseAction(EnemyPosition currentPosition, LinePosition linePosition) {
  if (behavior != NO) {
    followBehavior();
  }
  else {
    if (linePosition == CENTER_LINE) {
        behavior = TURN_AROUND;
        behavior_timer->reset();
        behavior_timer->start();
        behavior_timer->setTarget(500);
      }
    else if (linePosition == RIGHT_LINE) {
      motors->spinRight(100);
    }
    else if (linePosition == LEFT_LINE) {
      motors->spinLeft(100);
    }
    else {
      liveDrive(currentPosition, linePosition);
    }
  }

  if(currentPosition != lastEnemyPos && currentPosition != NONE) {
    lastEnemyPos = currentPosition;
  }
  
}

void algorithms::liveDrive(EnemyPosition currentPosition, LinePosition linePosition) {
  switch(currentPosition) {
    case LEFT:
      if(last_state_changed->elapsedMilliseconds() < 500) {
        switch(lastEnemyPos) {
          case FARFRONT:
            motors->customDrive(120, 80);
            break;
          case FRONT:
            motors->customDrive(120, 60);
            break;
          case MIDLEFT:
            motors->customDrive(120, 40);
            break;
          default:
            motors->spinLeft(100);
            break;
        }
      } else {
      motors->customDrive(120, 60);
      }
      break;
    case RIGHT:
      if(last_state_changed->elapsedMilliseconds() < 500) {
        switch(lastEnemyPos) {
          case FARFRONT:
            motors->customDrive(80, 120);
            break;
          case FRONT:
            motors->customDrive(60, 120);
            break;
          case MIDRIGHT:
            motors->customDrive(40, 120);
            break;
          default:
            motors->spinRight(100);
            break;
        }
      } else {
      motors->customDrive(60, 120);
      }
      break;
    case FRONT:
      if(last_state_changed->elapsedMilliseconds() < 500) {
        switch (lastEnemyPos) {
          case FARFRONT:
            motors->driveForward(250);
            break;
          case MIDLEFT:
            motors->customDrive(250, 225);
            break;
          case MIDRIGHT:
            motors->customDrive(225, 250);
            break;  
          default:
            motors->driveForward(250);
            break;
      }
      } else {
        motors->driveForward(250);
      }
      break;
    case MIDLEFT:
      if(last_state_changed->elapsedMilliseconds() < 500) {
        switch (lastEnemyPos) {
          case LEFT:
            motors->customDrive(130, 90);
            break;
          case FARFRONT:
            motors->customDrive(100, 120);
            break;  
          default:
            motors->customDrive(120, 90);
            break;
        }
      } else {
        motors->customDrive(120, 90);
      }
      break;
    case MIDRIGHT:
      if(last_state_changed->elapsedMilliseconds() < 500) {
        switch (lastEnemyPos) {
          case RIGHT:
            motors->customDrive(90, 130);
            break;
          case FARFRONT:
            motors->customDrive(120, 100);
            break;  
          default:
            motors->customDrive(90, 120);
            break;
      }
      } else {
        motors->customDrive(90, 120);
      }
      break;
    case FARFRONT:
      if(last_state_changed->elapsedMilliseconds() < 500) {
        switch (lastEnemyPos) {
          case LEFT:
            motors->customDrive(100, 120);
            break;
          case MIDLEFT:
            motors->customDrive(100, 120);
            break;
          case RIGHT:
            motors->customDrive(120, 100);
            break;  
          case MIDRIGHT:
            motors->customDrive(120, 100);
            break;  
          case FRONT:
            motors->driveForward(200);
            break;
          default:
            motors->driveForward(120);
            break;
        }
      } else {
        motors->driveForward(150);
      }
      break;
    case NONE:
      if(last_state_changed->elapsedMilliseconds() < 500) {
      switch (lastEnemyPos) {
          case LEFT:
            motors->customDrive(80, 50);
            break;
          case RIGHT:
            motors->customDrive(50, 80);
            break;
          case FARFRONT:
            motors->driveForward(80);
            break;
          case MIDLEFT:
            motors->customDrive(80, 60);
            break;
          case MIDRIGHT:
            motors->customDrive(60, 80);
            break;  
          default:
            motors->driveForward(80);
            break;
        }
      } else {
        motors->driveForward(80);
      }
      break;
  }
}

// void algorithms::respondToLine(LinePosition l) {
//   switch(l) {
//     case LEFT_LINE:
//       // turn right
//       motors->customDrive(80, 60);
//       break;

//     case RIGHT_LINE:
//       // turn left
//       motors->customDrive(60, 80);
//       break;

//     case CENTER_LINE:
//       motors->driveForward(80);
//       break;

//     default:
//       // do nothing
//       break;
//   }
// }

// void algorithms::drive_avgs(float* avgs) { 

//     // the average sight value hovers around 0.3 when nothing is seen
//     // so we map the range [0.3, 1.0] to [0.0, 1.0]
//     float avg_sight = max(((avgs[0] + avgs[1] + avgs[2])/3.0-0.3)/0.7, 0.0);
//     if (avg_sight < 0.1) {
//         avg_sight = 0.0;
//     }
//     // swaps from turing to charging as the vision improves
//     motors->customDrive(
//       static_cast<int>(min(static_cast<float>(-75 + 250 * avg_sight), 150.0f)), 
//       static_cast<int>(min(75, static_cast<int>(min(static_cast<float>(-75 + 250 * avg_sight), 150.0f))))
//     );
// }