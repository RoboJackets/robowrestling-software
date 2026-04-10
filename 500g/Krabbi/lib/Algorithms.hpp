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
    bool ChargeActive = false;
    float forwardAccel = 0.0f;
    int consecutiveChargeDetections = 0;

    int rampSpeed(unsigned long elapsed, int startSpeed, int endSpeed, unsigned long rampMs);
    void startBehavior(Behavior nextBehavior, unsigned long targetMs = 0);
    bool shouldCharge() const;
  public:
  
    algorithms(motor_actions& motors, world_state& world, timer& behavior_timer, timer& last_state_changed);

    void spin();
    void followBehavior();
    void respondToLine(LinePosition l);   // do something based on line_pos
    void selectMode(float imuForwardAccel = 0.0f);
    void chooseAction(EnemyPosition currentPosition, LinePosition linePosition);
    void liveDrive(EnemyPosition currentPosition, LinePosition linePosition);
};

#endif
