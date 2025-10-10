#ifndef ALGORITHMS_HPP
#define ALGORITHMS_HPP

#include "motor_actions.hpp"
#include "world_state.hpp"

class Algorithms {
  private:
    motor_actions* motors;
    world_state* world;

  public:
    Algorithms(motor_actions* motors, world_state* world);

    void respondToEnemy();  // do something based on enemy_pos
};

#endif