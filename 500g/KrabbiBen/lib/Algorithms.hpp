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
    bool forceFullCharge = false;
    unsigned long fullChargeLostStartMs = 0;
    float forwardAccel = 0.0f;
    int consecutiveChargeDetections = 0;
    float flagAttackStartYaw = 0.0f;
    float currentYaw = 0.0f;
    bool flagAttackStartYawCaptured = false;
    EnemyPosition previousDrivePosition = NONE;
    bool counterSpinActive = false;
    int counterSpinDirection = 0;
    unsigned long counterSpinStartMs = 0;

    int rampSpeed(unsigned long elapsed, int startSpeed, int endSpeed, unsigned long rampMs);
    void startBehavior(Behavior nextBehavior, unsigned long targetMs = 0);
    bool shouldCharge() const;
  public:
  
    algorithms(motor_actions& motors, world_state& world, timer& behavior_timer, timer& last_state_changed);

    void spin();
    void followBehavior();
    void respondToLine(LinePosition l);   // do something based on line_pos
    int swerveDirection = 0; // -1 for left, 1 for right
    void selectMode(float imuForwardAccel, int dip0, int dip1, float correctedYaw);
    void chooseAction(EnemyPosition currentPosition, LinePosition linePosition, float correctedYaw);
    void liveDrive(EnemyPosition currentPosition, LinePosition linePosition);
    void setFullChargeMode(bool enabled);
    bool isFullChargeMode() const;
    void resetState();
};

#endif
