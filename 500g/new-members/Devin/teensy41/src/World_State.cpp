#include "World_State.hpp"

World_State::World_State(int* lineSensors, int* irSensors) {
  this->lineSensors = lineSensors;
  this->irSensors = irSensors;
}

void World_State::checkConcurrency() {
  for (int i = 0; i < 3; i++) {
    if (irSensors[i] == 1) {
      concurrency[i]++;
    } else {
      concurrency[i] = 0;
    }
    irSensors[i] = (concurrency[i] >= 10) ? 1 : 0;
  }
}

LinePosition World_State::line_check() {
  bool left = lineSensors[0] > 620;
  bool right = lineSensors[1] > 775;

  if (left && right) return CENTER_LINE;
  if (left && !right) return LEFT_LINE;
  if (!left && right) return RIGHT_LINE;
  return OFF_LINE;
}

EnemyPosition World_State::enemy_pos() {
  // simple mapping to your enum values
  // adjust depending on how your IR sensors are arranged
  if (irSensors[1] == 1){
    if(irSensors[0] == 1 && irSensors[2] == 1) return FRONT;
    if (irSensors[0] == 1) return MIDLEFT;
    if (irSensors[2] == 1) return MIDRIGHT;
    return FARFRONT;
  } 
  if (irSensors[0] == 1) return LEFT;
  if (irSensors[2] == 1) return RIGHT;
  return NONE;
}
