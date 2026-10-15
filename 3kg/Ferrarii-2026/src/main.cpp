#include <Arduino.h>
#include <Bounce2.h>
#include "LineSensor.hpp"
#include "IRSensor.hpp"
#include "MotorDriver.hpp"
#include "RobotActions.hpp"
#include "WorldState.hpp"
#include "Brazil.hpp"
#include "BackNSmack.hpp"
#include "BackNDash.hpp"
#include "Track.hpp"
#include "Dash.hpp"
#include "Inch.hpp"

#define START_MOD 6

#define B_PWM 8
#define B_IN1 10
#define B_IN2 12
#define A_PWM 7
#define A_IN1 9
#define A_IN2 11

#define IR_B 31
#define IR_30L 34
#define IR_60L 35
#define IR_90L 36
#define IR_30R 30
#define IR_60R 29
#define IR_90R 28
#define IR_F 33

#define LN_RB1 A10
#define LN_RB2 A11
#define LN_RF1 A12
#define LN_RF2 A13
#define LN_LB1 A14
#define LN_LB2 A15
#define LN_LF1 A16
#define LN_LF2 A17

#define BATTERY_MONITOR 23 

#define LED1 20
#define LED2 15
#define LED3 14
#define LED4 17
#define LOW_BAT 2

#define TOP_BUTTON 21
#define BOT_BUTTON 22

Bounce2::Button top_button = Bounce2::Button();
Bounce2::Button bot_button = Bounce2::Button();

LineSensor* LN_LF;
LineSensor* LN_RF;
LineSensor* LN_LB;
LineSensor* LN_RB;

IRSensor* _IR_F;
IRSensor* _IR_30L;
IRSensor* _IR_60L;
IRSensor* _IR_90L;
IRSensor* _IR_30R;
IRSensor* _IR_60R;
IRSensor* _IR_90R;
IRSensor* _IR_B;

MotorDriver* motorDriver;
WorldState* worldState;
RobotActions* robotActions; 

Brazil* brazil;
BackNSmack* backNSmack;
BackNDash* backNDash;
Track* track;
Dash* dash;
Inch* inch;

bool led1 = LOW;
bool led2 = LOW;
int mode = 0;

const int THRESH_FACTOR = 150; // difference between black and white / 2

void writeMotors();
void pollSensors();
void debug();

void setup() {
  Serial.begin(9600);

  /* PIN MODES */

  pinMode(START_MOD, INPUT);

  pinMode(B_PWM, OUTPUT);
  pinMode(B_IN1, OUTPUT);
  pinMode(B_IN2, OUTPUT);
  pinMode(A_PWM, OUTPUT);
  pinMode(A_IN1, OUTPUT);
  pinMode(A_IN2, OUTPUT);

  pinMode(IR_B, INPUT_PULLDOWN);
  pinMode(IR_30L, INPUT_PULLDOWN);
  pinMode(IR_60L, INPUT_PULLDOWN);
  pinMode(IR_90L, INPUT_PULLDOWN);
  pinMode(IR_30R, INPUT_PULLDOWN);
  pinMode(IR_60R, INPUT_PULLDOWN);
  pinMode(IR_90R, INPUT_PULLDOWN);
  pinMode(IR_F, INPUT_PULLDOWN);

  pinMode(LN_RB1, INPUT);
  pinMode(LN_RB2, INPUT);
  pinMode(LN_RF1, INPUT);
  pinMode(LN_RF2, INPUT);
  pinMode(LN_LB1, INPUT);
  pinMode(LN_LB2, INPUT);
  pinMode(LN_LF1, INPUT);
  pinMode(LN_LF2, INPUT);

  pinMode(BATTERY_MONITOR, INPUT);

  pinMode(TOP_BUTTON, INPUT);
  pinMode(BOT_BUTTON, INPUT);

  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);
  pinMode(LED3, OUTPUT);
  pinMode(LED4, OUTPUT);
  pinMode(LOW_BAT, OUTPUT);

  /* Initialize Objects */

  LN_LF = new LineSensor();
  LN_RF = new LineSensor();
  LN_LB = new LineSensor();
  LN_RB = new LineSensor();

  _IR_F = new IRSensor();
  _IR_30L = new IRSensor();
  _IR_60L = new IRSensor();
  _IR_90L = new IRSensor();
  _IR_30R = new IRSensor();
  _IR_60R = new IRSensor();
  _IR_90R = new IRSensor();
  _IR_B = new IRSensor();

  motorDriver = new MotorDriver();
  robotActions = new RobotActions(motorDriver);
  worldState = new WorldState(
    LN_LF, 
    LN_RF, 
    LN_LB, 
    LN_RB,
    _IR_F,
    _IR_30L,
    _IR_60L,
    _IR_90L,
    _IR_30R,
    _IR_60R,
    _IR_90R,
    _IR_B
  );

  brazil = new Brazil(worldState, robotActions);
  backNSmack = new BackNSmack(worldState, robotActions);
  backNDash = new BackNDash(worldState, robotActions);
  track = new Track(worldState, robotActions);
  dash = new Dash(worldState, robotActions);
  inch = new Inch(worldState, robotActions);

  top_button.attach(TOP_BUTTON, INPUT_PULLUP); 
  top_button.interval(5); 
  top_button.setPressedState(LOW); 

  bot_button.attach(BOT_BUTTON, INPUT_PULLUP); 
  bot_button.interval(5); 
  bot_button.setPressedState(LOW); 

  /* START MODULE WAIT */

  while (!digitalRead(START_MOD)) {

      top_button.update();

      if (top_button.pressed()) {
        led1 = !led1;
        led2 = false;
        if (led1) {
          mode = 1;
        } else {
          mode = 0;
        }
      }

      bot_button.update();

      if (bot_button.pressed()) {
        led2 = !led2;
        led1 = false;
        if (led2) {
          mode = 2;
        } else {
          mode = 0;
        }
      }
    digitalWrite(LED1, led1);
    digitalWrite(LED2, led2);

    Serial.print(millis());
    Serial.print(": ");
    Serial.print(mode);
    Serial.print(" ");
    Serial.print(digitalRead(START_MOD));
    Serial.println(" Waiting for start signal");
  }

  /* Set line sensors threshold */

  LN_LF->setThreshold(analogRead(LN_LF1) - THRESH_FACTOR, analogRead(LN_LF2) - THRESH_FACTOR);
  LN_RF->setThreshold(analogRead(LN_RF1) - THRESH_FACTOR, analogRead(LN_RF2) - THRESH_FACTOR);
  LN_LB->setThreshold(analogRead(LN_LB1) - THRESH_FACTOR, analogRead(LN_LB2) - THRESH_FACTOR);
  LN_RB->setThreshold(analogRead(LN_RB1) - THRESH_FACTOR, analogRead(LN_RB2) - THRESH_FACTOR);
}

void loop() {
  /* Strategy 1 */
  if (mode == 0) {
    if (backNDash->run()) {
      if (!track->run()) {
        brazil->run();
      }
    }
  }
  /* Strategy 2 */
  if (mode == 1) {
    if (dash->run()) {
      if (!track->run()) {
        brazil->run();
      }
    }
  }
  /* Strategy 3 */
  if (mode == 2) {
    if (inch->run()) {
      if (!track->run()) {
        brazil->run();
      }
    }
  }

  debug();
  pollSensors();
  writeMotors();
  if (!digitalRead(START_MOD)) {
    while(true) {
      robotActions->brake();
      writeMotors();
      Serial.print(millis());
      Serial.println(": braking");
    }
  }
}

void pollSensors() {
  LN_LF->setValue(analogRead(LN_LF1), analogRead(LN_LF2));
  LN_RF->setValue(analogRead(LN_RF1), analogRead(LN_RF2));
  LN_LB->setValue(analogRead(LN_LB1), analogRead(LN_LB2));
  LN_RB->setValue(analogRead(LN_RB1), analogRead(LN_RB2));

  _IR_F->setValue(digitalRead(IR_F));
  _IR_30L->setValue(digitalRead(IR_30L));
  _IR_60L->setValue(digitalRead(IR_60L));
  _IR_90L->setValue(digitalRead(IR_90L));
  _IR_30R->setValue(digitalRead(IR_30R));
  _IR_60R->setValue(digitalRead(IR_60R));
  _IR_90R->setValue(digitalRead(IR_90R));
  _IR_B->setValue(digitalRead(IR_B));
}

void writeMotors() {
  if (motorDriver->getIsBraking() == true) {
    digitalWrite(A_IN1, 0);
    digitalWrite(A_IN2, 0);
    digitalWrite(B_IN1, 0);
    digitalWrite(B_IN2, 0);
    return;
  }

  /* LEFT MOTOR */
  if (motorDriver->getLeftDirection() == Direction::FORWARD) {
    digitalWrite(A_IN1, 0);
    digitalWrite(A_IN2, 1);
  } else {
    digitalWrite(A_IN1, 1);
    digitalWrite(A_IN2, 0);
  }
  analogWrite(A_PWM, motorDriver->getLeftSpeed());

  /* RIGHT MOTOR */
  if (motorDriver->getRightDirection() == Direction::FORWARD) {
    digitalWrite(B_IN1, 0);
    digitalWrite(B_IN2, 1);
  } else {
    digitalWrite(B_IN1, 1);
    digitalWrite(B_IN2, 0);
  }
  analogWrite(B_PWM, motorDriver->getRightSpeed());
}

void debug() {
  Serial.print(millis());
  Serial.print(": ");
  if (true) { //debug line sensors
    Serial.print(analogRead(LN_LF2));
    Serial.print(" ");
    Serial.print(analogRead(LN_LF1));
    Serial.print(" ");
    Serial.print(analogRead(LN_RF2));
    Serial.print(" ");
    Serial.print(analogRead(LN_RF1));
    Serial.print(" ");
    Serial.print(analogRead(LN_RB2));
    Serial.print(" ");
    Serial.print(analogRead(LN_RB1));
    Serial.print(" ");
    Serial.print(analogRead(LN_LB2));
    Serial.print(" ");
    Serial.print(analogRead(LN_LB1));
    Serial.print(" ");
  }
  if (true) {
    Serial.print(LN_LF->getValue());
    Serial.print(LN_RF->getValue());
    Serial.print(LN_LB->getValue());
    Serial.print(LN_RB->getValue());
    Serial.print(" ");
  }
  if (true) {
    Serial.print(digitalRead(IR_F));
    Serial.print(digitalRead(IR_30L));
    Serial.print(digitalRead(IR_60L));
    Serial.print(digitalRead(IR_90L));
    Serial.print(digitalRead(IR_30R));
    Serial.print(digitalRead(IR_60R));
    Serial.print(digitalRead(IR_90R));
    Serial.print(digitalRead(IR_B));
    Serial.print(" ");
  }
  if (true) {
    Serial.print(motorDriver->getLeftDirection());
    Serial.print(" ");
    Serial.print(motorDriver->getLeftSpeed());
    Serial.print(" ");
    Serial.print(motorDriver->getRightDirection());
    Serial.print(" ");
    Serial.print(motorDriver->getRightSpeed());
  }
  Serial.println();
}