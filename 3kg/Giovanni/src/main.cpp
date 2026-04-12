#include <Arduino.h>

// ===== PWM CONFIG (FROM WORKING CODE) =====
const int pwmResolutionBits = 8;
const int pwmMax = 255;
const uint32_t pwmHz = 20000; // 20 kHz

// ===== Output Pins (UPDATED TO MATCH WORKING SETUP) =====
const int leftPWM = 37;
const int leftDir = 38;
const int rightPWM = 36;
const int rightDir = 40;

// ===== Input Pins (UNCHANGED) =====
const int left90IR = 9;
const int right90IR = 28;
const int left60IR = 10;
const int right60IR = 27;
const int left45IR = 11;
const int right45IR = 26;
const int left30IR = 12;
const int right30IR = 25;
const int centerIR = 24;

const int frLine = 14;
const int flLine = 13;
const int brLine = 16;
const int blLine = 15;

const int startMod = 21;
bool started = false;

// ===== Arrays =====
int irArray[9];
int lineArray[4];
int driver[2]; // [-255, 255]

// ===== Dummy Classes (keep yours) =====
#include "Robot/Algorithms.hpp"
#include "Robot/RobotActions.hpp"
#include "Enumerations/EnemyPos.hpp"
#include "Enumerations/OnLine.hpp"

Algorithms *algo;
RobotActions *action;

// ===== Function Declarations =====
EnemyPos getEnemyPosition();
OnLine isOnLine();

// ===================== SETUP =====================
void setup() {
  // Motor Pins
  pinMode(leftPWM, OUTPUT);
  pinMode(leftDir, OUTPUT);
  pinMode(rightPWM, OUTPUT);
  pinMode(rightDir, OUTPUT);

  // PWM CONFIG (CRITICAL)
  analogWriteResolution(pwmResolutionBits);
  analogWriteFrequency(leftPWM, pwmHz);
  analogWriteFrequency(rightPWM, pwmHz);

  // Ensure motors OFF
  analogWrite(leftPWM, 0);
  analogWrite(rightPWM, 0);
  digitalWrite(leftDir, LOW);
  digitalWrite(rightDir, LOW);

  // Sensor Pins
  pinMode(left90IR, INPUT);
  pinMode(right90IR, INPUT);
  pinMode(left60IR, INPUT);
  pinMode(right60IR, INPUT);
  pinMode(left45IR, INPUT);
  pinMode(right45IR, INPUT);
  pinMode(left30IR, INPUT);
  pinMode(right30IR, INPUT);
  pinMode(centerIR, INPUT);

  pinMode(frLine, INPUT);
  pinMode(flLine, INPUT);
  pinMode(brLine, INPUT);
  pinMode(blLine, INPUT);

  pinMode(startMod, INPUT);

  // Classes
  action = new RobotActions(driver, driver + 1);
  algo = new Algorithms(action);
}

// ===================== SENSOR POLLING =====================
void pollSensors() {
  irArray[0] = digitalRead(left90IR);
  irArray[1] = digitalRead(left60IR);
  irArray[2] = digitalRead(left45IR);
  irArray[3] = digitalRead(left30IR);
  irArray[4] = digitalRead(centerIR);
  irArray[5] = digitalRead(right30IR);
  irArray[6] = digitalRead(right45IR);
  irArray[7] = digitalRead(right60IR);
  irArray[8] = digitalRead(right90IR);

  lineArray[0] = analogRead(flLine);
  lineArray[1] = analogRead(frLine);
  lineArray[2] = analogRead(brLine);
  lineArray[3] = analogRead(blLine);
}

// ===================== LOGIC =====================
void calcState() {
  EnemyPos enemyPos = getEnemyPosition();
  OnLine onLine = isOnLine();
  algo->selectAlgo(enemyPos, onLine);
}

// ===================== MOTOR OUTPUT =====================
void writeMotors() {
  int left = constrain(driver[0], -pwmMax, pwmMax);
  int right = constrain(driver[1], -pwmMax, pwmMax);

  // LEFT MOTOR
  digitalWrite(leftDir, left >= 0 ? HIGH : LOW);
  analogWrite(leftPWM, abs(100));

  // RIGHT MOTOR
  digitalWrite(rightDir, right >= 0 ? HIGH : LOW);
  analogWrite(rightPWM, abs(100));
}

void stopMotors() {
    int left = constrain(driver[0], -pwmMax, pwmMax);
    int right = constrain(driver[1], -pwmMax, pwmMax);

    int spd = 70;

    if (isOnLine() != NONELINE) {
      spd = 0;
    }

    // LEFT MOTOR
    digitalWrite(leftDir, left >= 0 ? HIGH : LOW);
    analogWrite(leftPWM, spd);
    // analogWrite(leftPWM, abs(left));

    // RIGHT MOTOR
    digitalWrite(rightDir, right >= 0 ? HIGH : LOW);
    analogWrite(rightPWM, spd);
    // analogWrite(rightPWM, abs(right));
}

// ===================== STATE HELPERS =====================
EnemyPos getEnemyPosition() {
  if (irArray[4] == 1) return FRONT;
  else if (irArray[0] || irArray[1] || irArray[2] || irArray[3]) return LEFT;
  else if (irArray[5] || irArray[6] || irArray[7] || irArray[8]) return RIGHT;
  return NONE;
}

OnLine isOnLine() {
  if (lineArray[1] == 1) {
    return FRLINE;
  } 
  else if (lineArray[2] == 1) {
    return FRLINE;
  } 
  else if (lineArray[0] == 1) {
    return BLLINE;
  } 
  else if (lineArray[3] == 1) {
    return BRLINE;
  }

  return NONELINE;
}

// ===================== LOOP =====================
void loop() {
    if (digitalRead(startMod) == 1) {
        if (started == true) {
            pollSensors();
            // calcState();
            writeMotors();

        } else {
            started = true;
            delay(5000);
        }
    } else {
        stopMotors();
    }
}