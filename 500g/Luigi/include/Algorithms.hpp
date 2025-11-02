#ifndef ALGORITHMS_HPP
#define ALGORITHMS_HPP

#include "motor_actions.hpp"
#include "world_state.hpp"


class algorithms {
  private:
    motor_actions* motors;
    world_state* world;
    timer* algo_timer;
    EnemyPosition lastEnemyPos = NONE;
    RobotMode mode = FOLLOW_LINE;
    EnemyPosition currentEnemyPos = NONE; 
    timer* last_state_changed;
  public:
  
    algorithms(motor_actions* motors, world_state* world, timer* algo_timer, timer* last_state_changed);

    void selectBehavior();
    void followBehavior(EnemyPosition e, LinePosition l);
    void respondToEnemy(EnemyPosition currentPosition);  // do something based on enemy_pos
    void respondToLine(LinePosition l);   // do something based on line_pos
    void drive_avgs(float* avgs);
};

#endif