#include "Algorithms.hpp"
#include "enums.hpp"
#include <Arduino.h>

algorithms::algorithms(motor_actions* motors, world_state* world, timer* algo_timer, timer* last_state_changed) {
  this->motors = motors;
  this->world = world;
  this->algo_timer = algo_timer;
  this->last_state_changed = last_state_changed;
}

void algorithms::selectBehavior() {
  EnemyPosition e = world->enemy_pos();
  if(currentEnemyPos != e && currentEnemyPos != NONE) {
    lastEnemyPos = currentEnemyPos;
    last_state_changed->reset();
    last_state_changed->start();
  }
  currentEnemyPos = e;
  LinePosition l = world->line_check();

  algo_timer->start();
  if (l == RIGHT_LINE || l == LEFT_LINE || l == CENTER_LINE) {
    mode = FOLLOW_LINE;
  }
  else {
    if (algo_timer->elapsedMilliseconds() < 5000) {

      if (e != lastEnemyPos && mode != ATTACK) {
        switch (e) {
          case LEFT:
            mode = AVOID_LEFT;
            break;
          case RIGHT:
            mode = AVOID_RIGHT;
            break;
          default:
            mode = ATTACK;
            break;
        }
      }
    }
    else {
      mode = ATTACK;
    }
  }
  followBehavior(e, l);
}

void algorithms::followBehavior(EnemyPosition e, LinePosition l) {
  switch (mode) {
    case FOLLOW_LINE:
      respondToLine(l);
      break;
    case ATTACK:
      respondToEnemy(e);
      break;
    case AVOID_LEFT:
      respondToEnemy(e);
      break;
    case AVOID_RIGHT:
      respondToEnemy(e);
      break;
    default:
      respondToLine(l);
      break;
  }
}

void algorithms::respondToEnemy(EnemyPosition currentPosition) {
  switch (mode) {
    case AVOID_LEFT:
      motors->customDrive(100,50);
      break;
    case AVOID_RIGHT:
      motors->customDrive(50,100);
      break;
    case ATTACK:
      switch(currentPosition) {
        case LEFT:
          if(last_state_changed->elapsedMilliseconds() < 2000) {
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
          if(last_state_changed->elapsedMilliseconds() < 2000) {
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
          if(last_state_changed->elapsedMilliseconds() < 2000) {
            switch (lastEnemyPos) {
              case FARFRONT:
                motors->driveForward(200);
                break;
              case MIDLEFT:
                motors->customDrive(200, 175);
                break;
              case MIDRIGHT:
                motors->customDrive(175, 200);
                break;  
              default:
                motors->driveForward(200);
                break;
          }
          } else {
            motors->driveForward(200);
          }
          break;
        case MIDLEFT:
          if(last_state_changed->elapsedMilliseconds() < 2000) {
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
          if(last_state_changed->elapsedMilliseconds() < 2000) {
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
          if(last_state_changed->elapsedMilliseconds() < 2000) {
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
          if(last_state_changed->elapsedMilliseconds() < 2000) {
           switch (lastEnemyPos) {
              case LEFT:
                motors->customDrive(120, 50);
                break;
              case RIGHT:
                motors->customDrive(50, 120);
                break;
              case FARFRONT:
                motors->driveForward(120);
                break;
              case MIDLEFT:
                motors->customDrive(110, 80);
                break;
              case MIDRIGHT:
                motors->customDrive(80, 110);
                break;  
              default:
                motors->driveForward(80);
                break;
            }
          } else {
            motors->driveForward(100);
          }
          break;
      }
      break;
    default:
      motors->driveForward(80);
      break;
  }

  if(currentPosition != lastEnemyPos && currentPosition != NONE) {
    lastEnemyPos = currentPosition;
  }
  
}

void algorithms::respondToLine(LinePosition l) {
  switch(l) {
    case LEFT_LINE:
      // turn right
      motors->customDrive(80, 60);
      break;

    case RIGHT_LINE:
      // turn left
      motors->customDrive(60, 80);
      break;

    case CENTER_LINE:
      motors->driveForward(80);
      break;

    default:
      // do nothing
      break;
  }
}

void algorithms::drive_avgs(float* avgs) { 

    // the average sight value hovers around 0.3 when nothing is seen
    // so we map the range [0.3, 1.0] to [0.0, 1.0]
    float avg_sight = max(((avgs[0] + avgs[1] + avgs[2])/3.0-0.3)/0.7, 0.0);
    if (avg_sight < 0.1) {
        avg_sight = 0.0;
    }
    // swaps from turing to charging as the vision improves
    motors->customDrive(
      static_cast<int>(min(static_cast<float>(-75 + 250 * avg_sight), 150.0f)), 
      static_cast<int>(min(75, static_cast<int>(min(static_cast<float>(-75 + 250 * avg_sight), 150.0f))))
    );
}