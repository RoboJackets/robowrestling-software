#ifndef ALGORITHMS_HPP
#define ALGORITHMS_HPP

#include "motor_actions.hpp"
#include "world_state.hpp"


class algorithms {
  private:
    motor_actions* motors;
    world_state* world;
    timer* behavior_timer;
    EnemyPosition lastEnemyPos = NONE;
    EnemyPosition currentEnemyPos = NONE; 
    Behavior behavior = NO;
    timer* last_state_changed;
  public:
  
    algorithms(motor_actions* motors, world_state* world, timer* behavior_timer, timer* last_state_changed);

    void selectMode();
    void followBehavior();
    void chooseAction(EnemyPosition currentPosition, LinePosition l);  // do something based on enemy_pos
    void liveDrive(EnemyPosition currentPosition, LinePosition l);
    // void respondToLine(LinePosition l);   // do something based on line_pos
    // void drive_avgs(float* avgs);
};

#endif