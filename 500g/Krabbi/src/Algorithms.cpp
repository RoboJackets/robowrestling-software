#include "Algorithms.hpp"
#include "enums.hpp"
#include <Arduino.h>
#include <math.h>

namespace {
constexpr unsigned long OPEN_ENDED_BEHAVIOR_MS = 2147483647UL;
constexpr unsigned long CHARGE_DURATION_MS = 140UL;
constexpr unsigned long CHARGE_COOLDOWN_MS = 220UL;
constexpr int SEARCH_FAST_SPEED = 90;
constexpr int SEARCH_SLOW_SPEED = 25;
constexpr int SIDE_SPIN_SPEED = 190;
constexpr int APPROACH_MIN_SPEED = 105;
constexpr int APPROACH_MAX_SPEED = 175;
constexpr int FAR_APPROACH_SPEED = 120;
constexpr int TRACK_OUTSIDE_SPEED = 175;
constexpr int TRACK_INSIDE_SPEED = 95;
constexpr int CHARGE_START_SPEED = 175;
constexpr int CHARGE_MAX_SPEED = 215;
constexpr float TIP_ABORT_ANGLE_DEG = 11.0f;
constexpr float MAX_SETTLED_FORWARD_ACCEL = 2.4f;
constexpr float CHARGE_ABORT_ACCEL = 3.4f;
constexpr int CHARGE_STABLE_DETECTIONS = 4;

bool isFrontArc(EnemyPosition position) {
  return position == FRONT || position == FARFRONT;
}

bool isLeftArc(EnemyPosition position) {
  return position == LEFT || position == MIDLEFT || position == FLAG_LEFT;
}

bool isRightArc(EnemyPosition position) {
  return position == RIGHT || position == MIDRIGHT || position == FLAG_RIGHT;
}
}

algorithms::algorithms(motor_actions& motors, world_state& world, timer& behavior_timer, timer& last_state_changed)
  : motors(motors), world(world), behavior_timer(behavior_timer), last_state_changed(last_state_changed) {
}

int algorithms::rampSpeed(unsigned long elapsed, int startSpeed, int endSpeed, unsigned long rampMs) {
  if (rampMs == 0 || elapsed >= rampMs) {
    return endSpeed;
  }

  return startSpeed + ((elapsed * (endSpeed - startSpeed)) / rampMs);
}

void algorithms::startBehavior(Behavior nextBehavior, unsigned long targetMs) {
  behavior = nextBehavior;
  behavior_timer.reset();
  behavior_timer.start();
  behavior_timer.setTarget(targetMs == 0 ? OPEN_ENDED_BEHAVIOR_MS : targetMs);
}

bool algorithms::shouldCharge() const {
  const bool frontLocked = consecutiveChargeDetections >= CHARGE_STABLE_DETECTIONS;
  const bool chargeReady = millis() >= chargeCooldownUntil;
  const bool upright = fabsf(pitchAngleDeg) <= TIP_ABORT_ANGLE_DEG;
  const bool settled = forwardAccel <= MAX_SETTLED_FORWARD_ACCEL;
  return frontLocked && chargeReady && upright && settled;
}

bool algorithms::shouldAbortCharge() const {
  return fabsf(pitchAngleDeg) > TIP_ABORT_ANGLE_DEG || forwardAccel > CHARGE_ABORT_ACCEL;
}

void algorithms::selectMode(float imuForwardAccel, float imuPitchDeg) {
  forwardAccel = imuForwardAccel;
  pitchAngleDeg = imuPitchDeg;

  EnemyPosition e = world.enemy_pos();
  if (currentEnemyPos != e) {
    if (currentEnemyPos != NONE) {
      lastEnemyPos = currentEnemyPos;
    }
    last_state_changed.reset();
    last_state_changed.start();
  }
  currentEnemyPos = e;

  if (!last_state_changed.isRunning()) {
    last_state_changed.start();
  }

  if (isFrontArc(currentEnemyPos)) {
    if (consecutiveChargeDetections < CHARGE_STABLE_DETECTIONS + 2) {
      consecutiveChargeDetections++;
    }
  } else if (consecutiveChargeDetections > 0) {
    consecutiveChargeDetections--;
  }

  LinePosition linePos = world.line_check();

  chooseAction(currentEnemyPos, linePos);
}

void algorithms::followBehavior() {
  // Fixed spin time: 70ms, rest is backup
  unsigned long spinTime = 70;
  unsigned long backupPhaseThreshold = currentEscapeDuration > spinTime ? currentEscapeDuration - spinTime : 0;
  
  switch (behavior) {
    case TURN_AROUND_R:
      if (behavior_timer.elapsedMilliseconds() < backupPhaseThreshold) {
        motors.driveBackward(180); 
      }
      else {
        motors.spinRight(180);
      }
      break;
    case TURN_AROUND_L:
      if (behavior_timer.elapsedMilliseconds() < backupPhaseThreshold) {
        motors.driveBackward(180);
      }
      else {
        motors.spinLeft(180);
      }
      break;
    case CHARGE:
      {
        unsigned long elapsed = behavior_timer.elapsedMilliseconds();
        int speed = rampSpeed(elapsed, CHARGE_START_SPEED, CHARGE_MAX_SPEED, CHARGE_DURATION_MS);
        motors.driveForward(speed);
      }
      break;
    case STEALTH_CHARGE:
      {
        unsigned long elapsed = behavior_timer.elapsedMilliseconds();
        int speed = rampSpeed(elapsed, 100, 180, 180);
        
        // Charge in the direction of the enemy
        switch(currentEnemyPos) {
          case MIDLEFT:
            motors.customDrive(255 * speed / 255, 200 * speed / 255);
            break;
          case MIDRIGHT:
            motors.customDrive(200 * speed / 255, 255 * speed / 255);
            break;
          default:
            motors.driveForward(speed);
            break;
        }
      }
      break;
    case FRONT_APPROACH:
      {
        unsigned long elapsed = behavior_timer.elapsedMilliseconds();
        int speed = rampSpeed(elapsed, 110, 255, 1000);
        motors.driveForward(speed);
      }
      break;
    case FLAG_ATTACK_L:
      // Spin sharply for 50ms, then punch forward at max speed for the remaining time
      if (behavior_timer.elapsedMilliseconds() < 50) {
        motors.spinLeft(255); 
      } else {
        motors.driveForward(255); 
      }
      break;

    case FLAG_ATTACK_R:
      if (behavior_timer.elapsedMilliseconds() < 50) {
        motors.spinRight(255);
      } else {
        motors.driveForward(255);
      }
      break;
    default:
      break;
  }
}

void algorithms::spin() {
  motors.customDrive(180, 90);//r, l
}

void algorithms::chooseAction(EnemyPosition currentPosition, LinePosition linePosition) {
  // === INITIALIZATION ===
  if (started == false) {
    behavior = HUNTING;
    started = true;
    last_state_changed.start();
    return;
  }

  // === PRIORITY 1: LINE ESCAPE ===
  if (linePosition != OFF_LINE) {
      ChargeActive = false;
      consecutiveChargeDetections = 0;
      if (linePosition == LEFT_LINE) {
          behavior = TURN_AROUND_R;
      } else if (linePosition == RIGHT_LINE) { 
          behavior = TURN_AROUND_L;
      }
      else if (linePosition == CENTER_LINE) {
          behavior = TURN_AROUND_L;
      }
      behavior_timer.reset();
      behavior_timer.start();
      
      unsigned long escapeDuration = 220;
      if (wasInLineEscape && behavior == HUNTING) {
          escapeDuration = (unsigned long)(lastLineEscapeDuration * 0.66f);
          if (escapeDuration < 100) escapeDuration = 100;
      }
      lastLineEscapeDuration = escapeDuration;
      currentEscapeDuration = escapeDuration;  
      behavior_timer.setTarget(escapeDuration);
      wasInLineEscape = true;
      return;
  }

  // === PRIORITY 2: FLAG COUNTER ===
  // Trigger the sequence if we see a flag while hunting or during opening charge
  if ((currentPosition == FLAG_LEFT || currentPosition == FLAG_RIGHT) && (behavior == HUNTING || behavior == CHARGE)) {
      startBehavior((currentPosition == FLAG_LEFT) ? FLAG_ATTACK_L : FLAG_ATTACK_R, 150);
      return; 
  }

  // === PRIORITY 3: TIMED BEHAVIORS (CHARGES, ESCAPES, FLAG ATTACKS) ===
  if (behavior != HUNTING) {
      if (behavior == CHARGE && (shouldAbortCharge() || (!isFrontArc(currentPosition) && currentPosition != MIDLEFT && currentPosition != MIDRIGHT))) {
          behavior = HUNTING;
          ChargeActive = false;
          chargeCooldownUntil = millis() + CHARGE_COOLDOWN_MS;
      }
      // Exit STEALTH_CHARGE early if enemy no longer in charge-able position
      if (behavior == STEALTH_CHARGE && currentPosition != FRONT && currentPosition != FARFRONT && currentPosition != MIDLEFT && currentPosition != MIDRIGHT) {
          behavior = HUNTING;
      }
      else if (behavior != HUNTING && behavior_timer.isFinished()) {
          if (behavior == CHARGE) {
            ChargeActive = false;
            chargeCooldownUntil = millis() + CHARGE_COOLDOWN_MS;
          }
          behavior = HUNTING;
          wasInLineEscape = false;  
      } else {
          followBehavior();
          return;
      }
  }

  // === PRIORITY 4: HUNT & ATTACK ===
  if (behavior == HUNTING) {
      liveDrive(currentPosition, linePosition);
  }

  if(currentPosition != lastEnemyPos && currentPosition != NONE) {
    lastEnemyPos = currentPosition;
  }
}

void algorithms::liveDrive(EnemyPosition currentPosition, LinePosition linePosition) {
  (void)linePosition;

  switch(currentPosition) {
    case LEFT:
      ChargeActive = false;
      motors.spinLeft(SIDE_SPIN_SPEED);
      break;
    case MIDLEFT:
      ChargeActive = false;
      motors.customDrive(TRACK_OUTSIDE_SPEED, TRACK_INSIDE_SPEED);
      break;
    case RIGHT:
      ChargeActive = false;
      motors.spinRight(SIDE_SPIN_SPEED);
      break;
    case MIDRIGHT:
      ChargeActive = false;
      motors.customDrive(TRACK_INSIDE_SPEED, TRACK_OUTSIDE_SPEED);
      break;
    case FRONT:
      if (shouldCharge()) {
        ChargeActive = true;
        startBehavior(CHARGE, CHARGE_DURATION_MS);
        followBehavior();
      } else {
        ChargeActive = false;
        unsigned long elapsed = last_state_changed.elapsedMilliseconds();
        int speed = rampSpeed(elapsed, APPROACH_MIN_SPEED, APPROACH_MAX_SPEED, 180);
        motors.driveForward(speed);
      }
      break;
    case FARFRONT:
      ChargeActive = false;
      motors.driveForward(FAR_APPROACH_SPEED);
      break;
    case NONE:
      ChargeActive = false;
      if (isLeftArc(lastEnemyPos)) {
          motors.customDrive(SEARCH_FAST_SPEED, SEARCH_SLOW_SPEED);
      } else if (isRightArc(lastEnemyPos)) {
          motors.customDrive(SEARCH_SLOW_SPEED, SEARCH_FAST_SPEED);
      } else if ((millis() / 300) % 2 == 0) {
          motors.customDrive(SEARCH_FAST_SPEED, SEARCH_SLOW_SPEED);
      } else {
          motors.customDrive(SEARCH_SLOW_SPEED, SEARCH_FAST_SPEED);
      }
      break;
    default:
      ChargeActive = false;
      motors.stop();
      break;
  }
}
