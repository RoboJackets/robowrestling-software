#include "Algorithms.hpp"
#include "enums.hpp"
#include <Arduino.h>
#include <algorithm>

algorithms::algorithms(motor_actions* motors, world_state* world) {
  this->motors = motors;
  this->world = world;
}

void algorithms::respondToEnemy() {
  EnemyPosition e = world->enemy_pos();
 
  switch(e) {
    case FRONT: 
    motors-> driveForward(120);
      break;
    case FARFRONT:
      // back up then spin to dodge
      motors->driveForward(60);
      
      break;

    case MIDLEFT:
      // gentle turn right to face enemy
      motors->customDrive(70, 60);
      break;

    case LEFT:
      // spin harder right
      motors->customDrive(85, 60);
      break;

    case MIDRIGHT:
      // gentle turn left
      motors->customDrive(60, 70);
      break;

    case RIGHT:
      // spin harder left
      motors->customDrive(60, 85);
      break;

    case NONE:
    default:
      // nothing detected — go forward slowly
      motors->spinLeft(60);
      break;
  }
   lastEnemyPos = e;
}

void algorithms::respondToLine() {
  LinePosition l = world->line_check();

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