#include "Algorithms.hpp"
#include "enums.hpp"
#include <Arduino.h>

namespace {
constexpr unsigned long OPEN_ENDED_BEHAVIOR_MS = 2147483647UL;
constexpr float CHARGE_ACCEL_THRESHOLD = -5.0f;
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
  return forwardAccel <= CHARGE_ACCEL_THRESHOLD;
}

void algorithms::selectMode(float imuForwardAccel) {
  forwardAccel = -imuForwardAccel;

  EnemyPosition e = world.enemy_pos();
  if(currentEnemyPos != e && currentEnemyPos != NONE) {
    lastEnemyPos = currentEnemyPos;
    last_state_changed.reset();
    last_state_changed.start();
  }
  currentEnemyPos = e;
  LinePosition linePos = world.line_check();

  chooseAction(currentEnemyPos, linePos);
}

void algorithms::followBehavior() {
  // Fixed spin time: 70ms, rest is backup
  unsigned long spinTime = 70;
  unsigned long backupPhaseThreshold = currentEscapeDuration > spinTime ? currentEscapeDuration - spinTime : 0;

  if (shouldCharge()) {
    ChargeActive = true;
  }
  
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
      motors.driveForward(255);
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
    return;
  }

  // === PRIORITY 1: LINE ESCAPE ===
  if (linePosition != OFF_LINE) {
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
      // Exit STEALTH_CHARGE early if enemy no longer in charge-able position
      if (behavior == STEALTH_CHARGE && currentPosition != FRONT && currentPosition != FARFRONT && currentPosition != MIDLEFT && currentPosition != MIDRIGHT) {
          behavior = HUNTING;
      }
      else if (behavior_timer.isFinished()) {
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
      motors.spinLeft(220);
      break;
    case RIGHT:
      motors.spinRight(220);
      break;
    case FRONT:
      // if (shouldCharge()) {
      //   if (!ChargeActive) {
      //     startBehavior(CHARGE);
      //     ChargeActive = true;
      //   }
      //   followBehavior();
      // } else {
      if (ChargeActive) {
        motors.driveForward(255);
      } else {
        motors.driveForward(100);
      }
      // }
      break;
    // case MIDLEFT:
    //   {
    //     unsigned long elapsed = last_state_changed.elapsedMilliseconds();
    //     int speed;
    //     if (elapsed < 100) {
    //       speed = 80 + ((elapsed * 70) / 100);
    //     } else {
    //       speed = 150;
    //     }
    //     motors.customDrive(speed, speed * 0.8);
    //   }
    //   break;
    // case MIDRIGHT:
    //   {
    //     unsigned long elapsed = last_state_changed.elapsedMilliseconds();
    //     int speed;
    //     if (elapsed < 100) {
    //       speed = 80 + ((elapsed * 70) / 100);
    //     } else {
    //       speed = 150;
    //     }
    //     motors.customDrive(speed, speed * 0.8);
    //   }
    //   break;
    case NONE:
      // Use a basic millis() alternating timer so it sweeps without blocking.
      if ((millis() / 300) % 2 == 0) {
          motors.customDrive(50, 10);
      } else {
          motors.customDrive(8, 50);
      }
      break;
  }
}
