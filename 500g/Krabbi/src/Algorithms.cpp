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
      case TURN_AROUND_R:
        if (behavior_timer->elapsedMilliseconds() < 200) {
          motors->driveBackward(275);
        }
        else {
          motors->spinRight(325);
        }
        break;
      case TURN_AROUND_L:
        if (behavior_timer->elapsedMilliseconds() < 200) {
          motors->driveBackward(275);
        }
        else {
          motors->spinLeft(325);
        }
        break;
      case CHARGE:
        motors->driveForward(200);
      default:
        break;
    }
  }
}

void algorithms::spin() {
  motors->customDrive(180, 90);//r, l
}

void algorithms::chooseAction(EnemyPosition currentPosition, LinePosition linePosition) {
  if (started == false) {
    behavior = CHARGE;
    behavior_timer->reset();
    behavior_timer->start();
    behavior_timer->setTarget(100);
    started = true;
  }
  else if (behavior != NO) {
    followBehavior();
  }
  else {
    if (linePosition == CENTER_LINE) {
        behavior = TURN_AROUND_R;
        behavior_timer->reset();
        behavior_timer->start();
        behavior_timer->setTarget(360);
      }
    else if (linePosition == RIGHT_LINE) {
      // motors->spinRight(100);
        behavior = TURN_AROUND_L;
        behavior_timer->reset();
        behavior_timer->start();
        behavior_timer->setTarget(360);
    }
    else if (linePosition == LEFT_LINE) {
      // motors->spinLeft(100);
        behavior = TURN_AROUND_R;
        behavior_timer->reset();
        behavior_timer->start();
        behavior_timer->setTarget(360);
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
      motors->spinLeft(240);
      break;
    case RIGHT:
      motors->spinRight(240);
      break;
    case FRONT:
      motors->driveForward(450);
      break;
    case MIDLEFT:
      if(last_state_changed->elapsedMilliseconds() < 750) {
        switch (lastEnemyPos) {
          case LEFT:
            motors->customDrive(125, 175);
            break;
          default:
            motors->customDrive(175, 125);
            break;
        }
      } else {
        motors->customDrive(175, 125);
      }
      break;
    case MIDRIGHT:
      if(last_state_changed->elapsedMilliseconds() < 750) {
        switch (lastEnemyPos) {
          default:
            motors->customDrive(125, 175);
            break;
      }
      } else {
        motors->customDrive(125, 175);
      }
      break;
    case FARFRONT:
      motors->driveForward(450);
      break;
    case NONE:
      // if(last_state_changed->elapsedMilliseconds() < 500) {
      // switch (lastEnemyPos) {
      //     case LEFT:
      //       motors->customDrive(75, 30);
      //       break;
      //     case RIGHT:
      //       motors->customDrive(30, 75);
      //       break;
      //     case FARFRONT:
      //       motors->driveForward(75);
      //       break;
      //     case MIDLEFT:
      //       motors->customDrive(75, 60);
      //       break;
      //     case MIDRIGHT:
      //       motors->customDrive(60, 75);
      //       break;  
      //     default:
      //       motors->driveForward(75);
      //       break;
      //   }
      // } else {
      motors->driveForward(60);
      // }
      break;
  }
}
