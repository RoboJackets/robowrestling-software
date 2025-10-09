#ifndef ALGORITHMS_HPP
#define ALGORITHMS_HPP

#include "motorActions.hpp"
#include "World_State.hpp"

class Algorithms {
  private:
    motorActions* motors;
    World_State* world;

  public:
    Algorithms(motorActions* motors, World_State* world);

    void respondToEnemy();  // do something based on enemy_pos
};

#endif
