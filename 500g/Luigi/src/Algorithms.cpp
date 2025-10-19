#include "Algorithms.hpp"
#include "enums.hpp"
#include <Arduino.h>
#include <algorithm>

algorithms::algorithms(motor_actions* motors, world_state* world, timer* algo_timer) {
  this->motors = motors;
  this->world = world;
  this->algo_timer = algo_timer;
}

void algorithms::selectBehavior() {
  EnemyPosition e = world->enemy_pos();
  LinePosition l = world->line_check();

  algo_timer->start();
  if (l == RIGHT_LINE || l == LEFT_LINE || l == CENTER_LINE) {
    mode = FOLLOW_LINE;
  }
  else {
    if (algo_timer->elapsedMilliseconds() < 5000) {
      if (e != lastEnemyPos) {
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
      
      break;
    case AVOID_RIGHT:
      break;
    case ATTACK:
      break;
    default:
      break;
  }


  lastEnemyPos = currentPosition;
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
    float avg_sight = std::max(((avgs[0] + avgs[1] + avgs[2])/3.0-0.3)/0.7, 0.0);
    if (avg_sight < 0.1) {
        avg_sight = 0.0;
    }
    // swaps from turing to charging as the vision improves
    motors->customDrive(
      static_cast<int>(std::min(static_cast<float>(-75 + 250 * avg_sight), 150.0f)), 
      static_cast<int>(std::max(75, static_cast<int>(std::min(static_cast<float>(-75 + 250 * avg_sight), 150.0f))))
    );
}