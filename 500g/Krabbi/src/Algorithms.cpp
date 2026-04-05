#include "Algorithms.hpp"
#include "enums.hpp"
#include <Arduino.h>

namespace {
constexpr unsigned long OPEN_ENDED_BEHAVIOR_MS = 2147483647UL;
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

void algorithms::selectMode(bool stealth, bool charge) {
  if (charge) {
    if (started == false) {
      startBehavior(CHARGE, 500);
      started = true;
    }
  }
  EnemyPosition e = world.enemy_pos();
  if(currentEnemyPos != e && currentEnemyPos != NONE) {
    lastEnemyPos = currentEnemyPos;
    last_state_changed.reset();
    last_state_changed.start();
  }
  currentEnemyPos = e;
  LinePosition linePos = world.line_check();

  chooseAction(currentEnemyPos, linePos, stealth);
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
      motors.driveForward(150);
      break;
    case STEALTH_CHARGE:
      {
        unsigned long elapsed = behavior_timer.elapsedMilliseconds();
        int speed = rampSpeed(elapsed, 100, 180, 180);
        
        // Charge in the direction of the enemy
        switch(currentEnemyPos) {
          case MIDLEFT:
            motors.customDrive(200 * speed / 255, 255 * speed / 255);
            break;
          case MIDRIGHT:
            motors.customDrive(255 * speed / 255, 200 * speed / 255);
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

void algorithms::chooseAction(EnemyPosition currentPosition, LinePosition linePosition, bool stealth) {
  if (started == false) {
    if (stealth) {
        startBehavior(STEALTH_CHARGE);
        started = true;
        return;
    } else {
        startBehavior(CHARGE, 300);
        started = true;
        return;
    }
  }

  // === PRIORITY 1: LINE SENSORS (ALWAYS CHECKED FIRST) ===
  // Line detection can interrupt ANY behavior except line escapes
  if (linePosition != OFF_LINE && (behavior == HUNTING || behavior == CHARGE || behavior == STEALTH_CHARGE || behavior == FLAG_ATTACK_L || behavior == FLAG_ATTACK_R)) {
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

  // In stealth mode, a confirmed front lock overrides the opening stealth charge.
  // FRONT means the three front-facing sensors agree on the target.
  if (stealth && currentPosition == FRONT) {
      if (!frontApproachActive || behavior != FRONT_APPROACH) {
          startBehavior(FRONT_APPROACH);
          frontApproachActive = true;
      }
      followBehavior();
      return;
  }

  if (behavior == FRONT_APPROACH && currentPosition != FRONT) {
      behavior = HUNTING;
      frontApproachActive = false;
  } else if (currentPosition != FRONT) {
      frontApproachActive = false;
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
      liveDrive(currentPosition, linePosition, stealth);
  }

  if(currentPosition != lastEnemyPos && currentPosition != NONE) {
    lastEnemyPos = currentPosition;
  }
}

void algorithms::liveDrive(EnemyPosition currentPosition, LinePosition linePosition, bool stealth) {
  switch(currentPosition) {
    case LEFT:
      motors.spinLeft(220);
      break;
    case RIGHT:
      motors.spinRight(220);
      break;
    case FRONT:
      if (!frontApproachActive) {
        startBehavior(FRONT_APPROACH);
        frontApproachActive = true;
      }
      followBehavior();
      break;
    case MIDLEFT:
      if (stealth) {
        // Stealth mode: gradual acceleration for MIDLEFT
        unsigned long elapsed = last_state_changed.elapsedMilliseconds();
        int speed;
        if (elapsed < 100) {
          speed = 100 + ((elapsed * 155) / 100);
        } else {
          speed = 255;
        }
        motors.customDrive(175 * speed / 255, 125 * speed / 255);
      } else {
        // Normal mode: instant turn
        motors.customDrive(175, 125);
      }
      break;
    case MIDRIGHT:
      if (stealth) {
        // Stealth mode: gradual acceleration for MIDRIGHT
        unsigned long elapsed = last_state_changed.elapsedMilliseconds();
        int speed;
        if (elapsed < 100) {
          speed = 100 + ((elapsed * 155) / 100);
        } else {
          speed = 255;
        }
        motors.customDrive(125 * speed / 255, 175 * speed / 255);
      } else {
        // Normal mode: instant turn
        motors.customDrive(125, 175);
      }
      break;
    case FARFRONT:
      motors.driveForward(255); 
      break;
    case NONE:
      if (stealth) {
          // --- STEALTH SCANNING MODE ---
          // Use a basic millis() alternating timer so it sweeps without blocking
          if ((millis() / 300) % 2 == 0) {
              motors.customDrive(50, 10); // Drift left
          } else {
              motors.customDrive(8, 50); // Drift right
          }
      } else {
          // --- NORMAL HUNTING MODE ---
          motors.driveForward(45);
      }
      break;
  }
}
