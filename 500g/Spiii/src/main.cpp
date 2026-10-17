#include <Arduino.h>
#include <Bounce2.h>
#include <Servo.h>

#include "IRSensor.hpp"
#include "LineSensor.hpp"
#include "MotorDriver.hpp"
#include "RobotAction.hpp"
#include "WorldState.hpp"
#include "Track.hpp"
#include "Brazil.hpp"

#define START_MOD 5
#define L_IN1 7
#define L_IN2 8
#define R_IN1 9
#define R_IN2 10
#define IR_45L 3
#define IR_90L 4
#define IR_45R 0
#define IR_90R 2
#define IR_F 1
#define LN_B 14
#define LN_RF 15
#define LN_LF 16
#define BATTERY_MONITOR 17
#define SERVO 6
#define LED1 11
#define LED2 12
#define BUTTON_1 21
#define BUTTON_2 20
#define DIP_1 23
#define DIP_2 22
#define LCD_SCL 19
#define LCD_SDA 18

/* ROBOT SPEED */
int speed = 100;

LineSensor* _LN_LF;
LineSensor* _LN_RF;
LineSensor* _LN_B;

IRSensor* _IR_F;
IRSensor* _IR_45L;
IRSensor* _IR_90L;
IRSensor* _IR_45R;
IRSensor* _IR_90R;

MotorDriver *leftMotorDriver;
MotorDriver *rightMotorDriver;
RobotAction *robotAction;
WorldState *worldState;
Track *track;
Brazil *brazil;

Servo servo;

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

  pinMode(L_IN1, OUTPUT);
  pinMode(L_IN2, OUTPUT);
  pinMode(R_IN1, OUTPUT);
  pinMode(R_IN2, OUTPUT);

  pinMode(IR_45L, INPUT_PULLDOWN);
  pinMode(IR_45R, INPUT_PULLDOWN);
  pinMode(IR_90L, INPUT_PULLDOWN);
  pinMode(IR_90R, INPUT_PULLDOWN);
  pinMode(IR_F, INPUT_PULLDOWN);

  pinMode(BATTERY_MONITOR, INPUT);

  pinMode(BUTTON_1, INPUT);
  pinMode(BUTTON_2, INPUT);

  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);

  servo.attach(SERVO);

  /* Initialize Objects */
  leftMotorDriver = new MotorDriver();
  rightMotorDriver = new MotorDriver(true);
  robotAction = new RobotAction(leftMotorDriver, rightMotorDriver, speed);

  _LN_LF = new LineSensor();
  _LN_RF = new LineSensor();
  _LN_B = new LineSensor();

  _IR_F = new IRSensor();
  _IR_45L = new IRSensor();
  _IR_90L = new IRSensor();
  _IR_45R = new IRSensor();
  _IR_90R = new IRSensor();

  worldState = new WorldState(
    _LN_LF,
    _LN_RF,
    _LN_B,
    _IR_45L,
    _IR_45R,
    _IR_90L,
    _IR_90R,
    _IR_F
  );

  track = new Track(worldState, robotAction);
  brazil = new Brazil(worldState, robotAction);

  servo.write(90);
  /* START MODULE WAIT */
  while (!digitalRead(START_MOD)) {
    Serial.print(millis());
    Serial.print(": ");
    Serial.print(mode);
    Serial.print(" ");
    Serial.print(digitalRead(START_MOD));
    Serial.println(" Waiting for start signal");
  }
  /* Set line sensors threshold */

  _LN_LF->setThreshold(analogRead(LN_LF) - THRESH_FACTOR);
  _LN_RF->setThreshold(analogRead(LN_RF) - THRESH_FACTOR);
  _LN_B->setThreshold(analogRead(LN_B) - THRESH_FACTOR);
  servo.write(5);
}


void loop() {
  debug();
  pollSensors();

  if (!track->run()) {
    brazil->run();
  }

  writeMotors();
  if (!digitalRead(START_MOD)) {
    servo.write(90);
    while(true) {
      robotAction->brake();
      writeMotors();
      Serial.print(millis());
      Serial.println(": braking");
    }
  }
}

void pollSensors() {
  _LN_LF->setValue(analogRead(LN_LF));
  _LN_RF->setValue(analogRead(LN_RF));
  _LN_B->setValue(analogRead(LN_B));

  _IR_F->setValue(digitalRead(IR_F));
  _IR_90L->setValue(digitalRead(IR_90L));
  _IR_90R->setValue(digitalRead(IR_90R));
  _IR_45L->setValue(digitalRead(IR_45L));
  _IR_45R->setValue(digitalRead(IR_45R));
}

void writeMotors() {
  analogWrite(R_IN1, rightMotorDriver->getIn1());
  analogWrite(R_IN2, rightMotorDriver->getIn2());
  analogWrite(L_IN1, leftMotorDriver->getIn1());
  analogWrite(L_IN2, leftMotorDriver->getIn2());
}

void debug() {
  if (true) {
    Serial.print(millis());
    Serial.print(": ");
  }
  if (false) {
    Serial.print(leftMotorDriver->getIn1());
    Serial.print(leftMotorDriver->getIn2());
    Serial.print(" ");
    Serial.print(rightMotorDriver->getIn1());
    Serial.print(rightMotorDriver->getIn2());
    Serial.print(" ");
  }
  if (true) {
    Serial.print(digitalRead(START_MOD));
    Serial.print(" ");
    Serial.print(_IR_90L->getValue());
    Serial.print(_IR_45L->getValue());
    Serial.print(_IR_F->getValue());
    Serial.print(_IR_45R->getValue());
    Serial.print(_IR_90R->getValue());
    Serial.print(" ");
    Serial.print(digitalRead(IR_90L));
    Serial.print(digitalRead(IR_45L));
    Serial.print(digitalRead(IR_F));
    Serial.print(digitalRead(IR_45R));
    Serial.print(digitalRead(IR_90R));
    Serial.print(" ");
    Serial.print(analogRead(LN_LF));
    Serial.print(" ");
    Serial.print(analogRead(LN_RF));
    Serial.print(" ");
    Serial.print(analogRead(LN_B));
    Serial.print(" ");
  }
  Serial.println();
}