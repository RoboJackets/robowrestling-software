#ifndef ALGORITHMS_HPP
#define ALGORITHMS_HPP

#include "motor_actions.hpp"
#include "world_state.hpp"


class algorithms {
  private:
    motor_actions* motors;
    world_state* world;
    EnemyPosition lastEnemyPos = NONE;
  public:
    algorithms(motor_actions* motors, world_state* world);

    void respondToEnemy();  // do something based on enemy_pos
    void respondToLine();   // do something based on line_pos
    void drive_avgs(float* avgs);
};

#endif