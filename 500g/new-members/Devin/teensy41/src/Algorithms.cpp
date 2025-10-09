#include "algorithms.hpp"
#include <Arduino.h>

Algorithms::Algorithms(motorActions* motors, World_State* world) {
  this->motors = motors;
  this->world = world;
}

void Algorithms::respondToEnemy() {
  EnemyPosition e = world->enemy_pos();

  switch(e) {
    case FRONT: 
    motors-> driveForward(100);
      break;
    case FARFRONT:
      // back up then spin to dodge
      motors->driveForward(50);
      
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
}
