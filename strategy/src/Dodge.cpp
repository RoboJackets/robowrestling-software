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
  /*
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
  */
  switch (state) {
  case FORWARD:
    std::cout << "FORWARD\n";
    output[0] = 100;
    output[1] = 100;
    break;
  case RIGHT:
    std::cout << "RIGHT\n";
    output[0] = 0;
    output[1] = 100;
    break;
  case LEFT:
    std::cout << "LEFT\n";
    output[0] = 100;
    output[1] = 0;
    break;
  case SNEAKING:
    std::cout << "SNEAKING\n";
    output[0] = 50;
    output[1] = 50;
    break;
  
  default:
    std::cout << "WAITING\n";
    output[0] = 0;
    output[1] = 0;
    break;
  } //switch


    
  return std::vector<int>(output, output + sizeof(output)/sizeof(int));
}

// Checks sensors and returns the appropriate state of action
Dodge::State Dodge::update_state(SensorData input) {

  #define dist input.dist_buffer_

  //  return RIGHT;
  
  /*
  std::cout << "dist[0]: " << dist[0] << "\n";
  std::cout << "dist[1]: " << dist[1] << "\n";
  std::cout << "dist[2]: " << dist[2] << "\n";
  std::cout << "dist[3]: " << dist[3] << "\n";
  std::cout << "dist[4]: " << dist[4] << "\n";
  std::cout << "dist[5]: " << dist[5] << "\n\n";
  */
  int distSum = 0;
  for (int i = 0; i < 6; i++) {
    distSum = distSum + dist[i];
  } //For
  
  //If general all of the sensors read an approaching enemy, turns right.
  //During a head on collision, mainly 3 of the sensers approach low numbers.
  if (distSum <= 650) {
    //std::cout << "Very Close, Moving Forward\n";
    return RIGHT;
    //Left/Right: 100

    //If we don't see the enemy, we assume we are Sneaking to the enemy's side.
  } else if (distSum > 700) {
    
    return SNEAKING;
    
  } //Else-if

  
    /*    
  } else if (distSum >= 750) {
    return LEFT;
  } //If
  /*
      
    
  //If any distance sensor is less then 90cm.
  if (dist[0] <= 90 || dist[2] <= 90 || dist[3] <= 90 || dist[5] <= 90) {
    //Turn Right until dist[2] is greater than 150.
    return RIGHT;
    //Left: -100
    //Right: 100
  } //If

  //If the enemy distance from the center is 'far'.
  if (dist[2] <= 150 && dist[2] > 90) {

    //Turn Right until dist[2] is greater than 150.
    return FORWARD;
    //Left: -100
    //Right: 100
  } //If
  */
}
