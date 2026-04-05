#ifndef ALGORITHMS_HPP
#define ALGORITHMS_HPP

#include "motor_actions.hpp"
#include "world_state.hpp"


class algorithms {
  private:
    motor_actions& motors;
    world_state& world;
    timer& behavior_timer;
    EnemyPosition lastEnemyPos = NONE;
    EnemyPosition currentEnemyPos = NONE; 
    Behavior behavior = HUNTING;
    bool started = false;
    timer& last_state_changed;
    unsigned long lastLineEscapeDuration = 220;
    unsigned long currentEscapeDuration = 220;
    bool wasInLineEscape = false;
  public:
  
    algorithms(motor_actions& motors, world_state& world, timer& behavior_timer, timer& last_state_changed);

    void spin();
    void followBehavior();
    void chooseAction(EnemyPosition currentPosition, LinePosition l);  // do something based on enemy_pos
    void liveDrive(EnemyPosition currentPosition, LinePosition l);
    void respondToLine(LinePosition l);   // do something based on line_pos
    // void drive_avgs(float* avgs);

    // Update these three declarations in your header file
    void selectMode(bool stealth = false, bool charge = false); 
    void chooseAction(EnemyPosition currentPosition, LinePosition linePosition, bool stealth);
    void liveDrive(EnemyPosition currentPosition, LinePosition linePosition, bool stealth);
};

#endif