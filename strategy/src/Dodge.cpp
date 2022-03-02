#include <strategy/Dodge.h>
#include <iostream>

// Create and initialize data needed for the strategy
Dodge::Dodge() {
  state = IDLE;
}

// Returns the intended action in the format {Left Motor Power %, Right Motor Power %}
std::vector<int> Dodge::next_action(SensorData input) {
  int output[] = {0, 0};
  state = update_state(input);

  switch (state) {
  case IDLE:
    output[0] = 0;
    output[1] = 0;
    break;
  case APPROACH:
    output[0] = 80;
    output[1] = 80;
    break;
  case TURN_LEFT:
    output[0] = -50;
    output[1] = 50;
    break;
  case TURN_RIGHT:
    output[0] = 50;
    output[1] = -50;
    break;
  default:
    break;
  }

  return std::vector<int>(output, output + sizeof(output)/sizeof(int));
}

// Checks sensors and returns the appropriate state of action
Dodge::State Dodge::update_state(SensorData input) {
  
}