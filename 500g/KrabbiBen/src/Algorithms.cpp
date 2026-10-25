#include "Algorithms.hpp"
#include "enums.hpp"
#include <Arduino.h>

namespace {
constexpr unsigned long OPEN_ENDED_BEHAVIOR_MS = 2147483647UL;
constexpr float CHARGE_ACCEL_THRESHOLD = -4.0f;
constexpr int FULL_CHARGE_SPEED = 180;
constexpr unsigned long FULL_CHARGE_MAX_MS = 150;
constexpr unsigned long LINE_BACKUP_MS = 175; // test
constexpr int LINE_BACKUP_SPEED = 140;
constexpr unsigned long LINE_TURN_MS = 100;
constexpr int REGULAR_ENGAGE_SPEED = 87;
constexpr int REGULAR_ENGAGE_BIAS = 20;
constexpr unsigned long SWERVE_TURN_MS = 100; 
constexpr unsigned long SWERVE_FWD_MS = 230;  
constexpr unsigned int SWERVE_TURN_SPEED = 80;
constexpr unsigned long PREV_STATE_WINDOW_MS = 150;
constexpr unsigned long COUNTER_SPIN_MS = 20;
constexpr int COUNTER_SPIN_SPEED = 130;

constexpr unsigned long SENTRY_CHARGE_DELAY_MS = 500; 
static bool sentryModeEnabled = false;
static unsigned long sentryTargetTimer = 0;
}

algorithms::algorithms(motor_actions& motors, world_state& world, timer& behavior_timer, timer& last_state_changed)
  : motors(motors), world(world), behavior_timer(behavior_timer), last_state_changed(last_state_changed) {}

void algorithms::startBehavior(Behavior nextBehavior, unsigned long targetMs) {
  behavior = nextBehavior;
  behavior_timer.reset();
  behavior_timer.start();
  behavior_timer.setTarget(targetMs == 0 ? OPEN_ENDED_BEHAVIOR_MS : targetMs);
}

// Translates DIP switch settings into startup behaviors (Sentry, Swerve, or Hunt)
void algorithms::selectMode(float imuForwardAccel, int dip0, int dip1, float correctedYaw) {
  forwardAccel = -imuForwardAccel;
  EnemyPosition e = world.enemy_pos();
  
  if (currentEnemyPos != e && currentEnemyPos != NONE) {
    lastEnemyPos = currentEnemyPos;
    last_state_changed.reset();
    last_state_changed.start();
  }
  
  currentEnemyPos = e;
  LinePosition linePos = world.line_check();

  if (!started) {
    started = true;
    if (dip0 == LOW && dip1 == LOW) {
        sentryModeEnabled = true; 
        behavior = HUNTING; 
    }
    else if (dip0 == LOW && dip1 == HIGH) {
        swerveDirection = -1; // Left
        startBehavior(SWERVE_TURN_1, SWERVE_TURN_MS);
    } 
    else if (dip1 == LOW && dip0 == HIGH) {
        swerveDirection = 1;  // Right
        startBehavior(SWERVE_TURN_1, SWERVE_TURN_MS);
    } 
    else {
        behavior = HUNTING;  
    }
  }

  currentYaw = correctedYaw;  
  chooseAction(currentEnemyPos, linePos, correctedYaw);
}

// Triggers an aggressive push when the IMU detects an impact
void algorithms::setFullChargeMode(bool enabled) {
  // An impact must not replace an unfinished edge escape or reset its timer.
  if (behavior == TURN_AROUND_L || behavior == TURN_AROUND_R) {
    forceFullCharge = false;
    return;
  }
  if (enabled && forceFullCharge) return;
  forceFullCharge = enabled;
  if (enabled) {
    sentryModeEnabled = false; // Permanently wake Sentry if rammed
    startBehavior(FULL_CHARGE, FULL_CHARGE_MAX_MS);
  } else {
    behavior = HUNTING;
  }
}

bool algorithms::isFullChargeMode() const {
  return forceFullCharge;
}

void algorithms::resetState() {
  started = false;
  behavior = HUNTING;
  forceFullCharge = false;
  counterSpinActive = false;
  counterSpinDirection = 0;
  previousDrivePosition = NONE;
  currentEnemyPos = NONE;
  lastEnemyPos = NONE;
  lineEscapeTurning = false;

  sentryModeEnabled = false;
  sentryTargetTimer = 0;

  behavior_timer.reset();
  last_state_changed.reset();
  motors.stop();
}

// Executes the active behavior state (Line Escape, Charge, etc.)
void algorithms::followBehavior() {
  switch (behavior) {
    case TURN_AROUND_R:
      if (!lineEscapeTurning) motors.driveBackward(LINE_BACKUP_SPEED);
      else motors.spinRight(210);
      break;
    case TURN_AROUND_L:
      if (!lineEscapeTurning) motors.driveBackward(LINE_BACKUP_SPEED);
      else motors.spinLeft(210);
      break;
    case CHARGE:
    case STEALTH_CHARGE:
    case FRONT_APPROACH:
      liveDrive(currentEnemyPos, OFF_LINE);
      break;
    case FLAG_ATTACK_L:
      if (behavior_timer.elapsedMilliseconds() < 30) motors.spinLeft(200);   
      else motors.driveForward(FULL_CHARGE_SPEED);
      break;
    case FLAG_ATTACK_R:
      if (behavior_timer.elapsedMilliseconds() < 30) motors.spinRight(200);  
      else motors.driveForward(FULL_CHARGE_SPEED);
      break;
    case FULL_CHARGE:
      motors.driveForward(FULL_CHARGE_SPEED);
      break;
    case SWERVE_TURN_1:
      if (swerveDirection == 1) {
          motors.spinRight(SWERVE_TURN_SPEED);
      } else {
          motors.spinLeft(SWERVE_TURN_SPEED);
      }
      break;
    case SWERVE_FORWARD: // Ensure 'SWERVE_FWD' matches whatever enum name you have in enums.hpp
      motors.driveForward(FULL_CHARGE_SPEED);
      break;

    default:
      break;
  }
}

bool algorithms::respondToLine(LinePosition linePosition) {
  bool escapingLine = (behavior == TURN_AROUND_L || behavior == TURN_AROUND_R);
  if (!escapingLine && linePosition == OFF_LINE) return false;

  // Every forward behavior yields to the border, including timed openings.
  forceFullCharge = false;
  counterSpinActive = false;
  if (!escapingLine) {
    lineEscapeTurning = false;
    // Latch the turn direction from the first detection for this entire escape.
    // Left sensor -> right turn; right sensor -> left turn. If both are first
    // detected in the same poll, retain the existing left-turn fallback.
    startBehavior((linePosition == LEFT_LINE) ? TURN_AROUND_R : TURN_AROUND_L, LINE_BACKUP_MS);
  }

  if (lineEscapeTurning && linePosition != OFF_LINE) {
    // Do not chain reverse bursts when the border reappears during a turn.
    motors.stop();
    behavior_timer.reset();
    return true;
  }

  if (!lineEscapeTurning) {
    if (!behavior_timer.isFinished()) {
      motors.driveBackward(LINE_BACKUP_SPEED);
      return true;
    }
    if (linePosition != OFF_LINE) {
      // Reverse has a hard time limit even if a digital sensor stays LOW.
      motors.stop();
      return true;
    }
    // Start a full turn only after backing up AND clearing both sensors.
    lineEscapeTurning = true;
    startBehavior(behavior, LINE_TURN_MS);
  }

  if (!behavior_timer.isRunning()) startBehavior(behavior, LINE_TURN_MS);

  if (!behavior_timer.isFinished()) {
    followBehavior();
    return true;
  }

  behavior = HUNTING;
  lineEscapeTurning = false;
  return false;
}

void algorithms::chooseAction(EnemyPosition currentPosition, LinePosition linePosition, float correctedYaw) {
  if (respondToLine(linePosition)) return;

  // 3. IMU Collision / Full Charge Logic
  if (forceFullCharge) {
      bool enemyInFrontArc = (currentPosition == FRONT || currentPosition == FRONT_LEFT || currentPosition == FRONT_RIGHT || currentPosition == MIDLEFT || currentPosition == MIDRIGHT); 
      if (enemyInFrontArc && !behavior_timer.isFinished()) {
          behavior = FULL_CHARGE;
          followBehavior();
          return;
      } else {
          forceFullCharge = false;
          behavior = HUNTING;
      }
  }

  // 4. Edge Flag Attacks
  if ((currentPosition == FLAG_LEFT || currentPosition == FLAG_RIGHT) && behavior == HUNTING) {
      startBehavior((currentPosition == FLAG_LEFT) ? FLAG_ATTACK_L : FLAG_ATTACK_R, 150);
      return; 
  }

  // Fallback state management
  if (behavior != HUNTING) {
      if (behavior == CHARGE || behavior == STEALTH_CHARGE || behavior == FRONT_APPROACH) {
          behavior = HUNTING;
      } else if (behavior_timer.isFinished()) {
        if (behavior == SWERVE_TURN_1) {
              startBehavior(SWERVE_FORWARD, SWERVE_FWD_MS);
          } else {
              behavior = HUNTING;
          }
      } else {
          followBehavior();
          return;
      }
  }

  if (behavior == HUNTING) {
      liveDrive(currentPosition, linePosition);
  }

  if(currentPosition != lastEnemyPos && currentPosition != NONE) {
    lastEnemyPos = currentPosition;
  }
}

// Actively tracks and moves towards the target using IR data
void algorithms::liveDrive(EnemyPosition currentPosition, LinePosition linePosition) {
  (void)linePosition;
  unsigned long nowMs = millis();

if (currentPosition != previousDrivePosition) {
    // FIX: Only counter-spin if we completely lose sight of the enemy (NONE).
    // This stops the bot from violently braking when the enemy just shifts toward the center.
    if (previousDrivePosition == LEFT && currentPosition == NONE) {
      counterSpinActive = true;
      counterSpinDirection = 1;  
      counterSpinStartMs = nowMs;
    } else if (previousDrivePosition == RIGHT && currentPosition == NONE) {
      counterSpinActive = true;
      counterSpinDirection = -1; 
      counterSpinStartMs = nowMs;
    }
    previousDrivePosition = currentPosition;
  }

  // OPTIMIZED COUNTER-SPIN: No longer blind to the enemy!
  if (counterSpinActive) {
    unsigned long counterSpinElapsed = nowMs - counterSpinStartMs;
    
    // Check if the enemy has re-entered our strike zone during the spin
    bool targetReacquired = (currentPosition == FRONT || currentPosition == FRONT_LEFT || currentPosition == FRONT_RIGHT || currentPosition == MIDLEFT || currentPosition == MIDRIGHT || currentPosition == FARFRONT);

    if (counterSpinElapsed < COUNTER_SPIN_MS && counterSpinElapsed < PREV_STATE_WINDOW_MS && !targetReacquired) {
      if (counterSpinDirection > 0) motors.spinRight(COUNTER_SPIN_SPEED);
      else motors.spinLeft(COUNTER_SPIN_SPEED);
      return; // Keep spinning because we haven't found them yet
    }
    
    // If we get here, either the spin time is up, OR we instantly found the enemy!
    counterSpinActive = false;
    counterSpinDirection = 0;
  }

  // --- SENTRY MODE OVERRIDE ---
  if (sentryModeEnabled) {
      bool inFrontArc = (currentPosition == FRONT || currentPosition == FRONT_LEFT || currentPosition == FRONT_RIGHT || currentPosition == MIDLEFT || currentPosition == MIDRIGHT || currentPosition == FARFRONT);

      if (inFrontArc) {
          if (sentryTargetTimer == 0) sentryTargetTimer = millis(); 

          if (millis() - sentryTargetTimer >= SENTRY_CHARGE_DELAY_MS) {
              sentryModeEnabled = false; // Time's up, attack normally
          } else {
              switch(currentPosition) {
                  case FRONT:
                  case FARFRONT:    motors.stop(); break; // Stare down
                  case FRONT_LEFT:  motors.spinLeft(45); break; 
                  case FRONT_RIGHT: motors.spinRight(45); break;
                  case MIDLEFT:     motors.spinLeft(90); break; 
                  case MIDRIGHT:    motors.spinRight(90); break;
                  default:          break;
              }
              return; 
          }
      } else {
          sentryTargetTimer = 0; 
          if (currentPosition == NONE) {
              motors.stop(); 
              return;
          }
      }
  }

// --- NORMAL DRIVING LOGIC ---
  switch(currentPosition) {
    case LEFT:
      // Tweaked: 200 is a bit punchier than 180, but keeps centrifugal force lower than 240
      motors.spinLeft(200); 
      break;
    case RIGHT:
      motors.spinRight(200); 
      break;
    case FRONT:
      motors.driveForward(REGULAR_ENGAGE_SPEED);
      break;
    case FRONT_LEFT:
      motors.customDrive(REGULAR_ENGAGE_SPEED, REGULAR_ENGAGE_SPEED - REGULAR_ENGAGE_BIAS * 1.5);
      break;
    case FRONT_RIGHT:
      motors.customDrive(REGULAR_ENGAGE_SPEED - REGULAR_ENGAGE_BIAS * 1.5, REGULAR_ENGAGE_SPEED);
      break;
    case MIDLEFT:
      // Smoother Arc: Right wheel pushes moderately (50+30=80), Left drops slightly (50-10=40)
      // This prevents the violent jerk that whips the flags forward.
      motors.customDrive(REGULAR_ENGAGE_SPEED + 30, REGULAR_ENGAGE_SPEED - 10);
      break;
    case MIDRIGHT:
      // Smoother Arc: Right wheel drops slightly (50-10=40), Left pushes moderately (50+30=80)
      motors.customDrive(REGULAR_ENGAGE_SPEED - 10, REGULAR_ENGAGE_SPEED + 30);
      break;
    case FARFRONT:
      motors.driveForward(REGULAR_ENGAGE_SPEED);
      break;
    case NONE:
      if ((millis() % 600) < 300) {
          motors.customDrive(50, 10);
      } else {
          motors.customDrive(8, 50);
      }
      break;
    default:
      motors.stop();
      break;
  }
}
