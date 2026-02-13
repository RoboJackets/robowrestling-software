#include <Arduino.h>
#include "world_state.hpp"
#include "motor_actions.hpp"
#include "timer.hpp"
#include "Algorithms.hpp"

const int leftSideSensor = PA2;
const int leftSensor = PA3;
const int middleSensor = PA4;
const int rightSensor = PA5;
const int rightSideSensor = PA6;

const int rightB = PB6; // Don't know which is forward and backward
const int rightF = PB7;
const int leftB = PA8; // Don't know which is forward and backward 
const int leftF = PA9;

const int screenSCL = PB8;
const int screenSDA = PB9; 

const int startPin = PB10;
const int leftLineSensor = PA7;
const int rightLineSensor = PB0;

const int imuSCL = PB8;
const int imuSDA = PB9;

const int servoPin = PA1;

const int led1Pin = PB5;
const int led2Pin = PB1;

const int dip1 = PB12;
const int dip2 = PB13;
const int dip3 = PB14;

const int pushButton = PB4;

long currentMillis = 0;
int printCounter = 0;

float* avgs;
int motors[2] = {0};
int dips[3] = {0};
int line_sensors[2] = {0};
int ir_sensors[5] = {0};

timer* last_enemy_changed = new timer(&currentMillis);
timer* behavior_timer = new timer(&currentMillis);
world_state* ws = new world_state(line_sensors, ir_sensors);
motor_actions* ma = new motor_actions(motors);
algorithms* algo = new algorithms(ma, ws, last_enemy_changed, behavior_timer);

void pullSensors();
void writeMotors();
void debug();
void debugLine();
void debugLineLP(LinePosition lp);
void debugIR();
void debugAverages();
void debugEnemy(EnemyPosition ep);

void setup() {
  pinMode(leftSensor, INPUT);
  pinMode(middleSensor, INPUT);
  pinMode(rightSensor, INPUT);
  pinMode(leftSideSensor, INPUT);
  pinMode(rightSideSensor, INPUT);
  pinMode(startPin, INPUT);

  pinMode(rightF, OUTPUT);
  pinMode(rightB, OUTPUT);
  pinMode(leftF, OUTPUT);
  pinMode(leftB, OUTPUT);

  pinMode(leftLineSensor, INPUT);
  pinMode(rightLineSensor, INPUT);
  pinMode(dip1, INPUT_PULLUP);
  pinMode(dip2, INPUT_PULLUP);
  pinMode(pushButton, INPUT);
  pinMode(0, OUTPUT);

  Serial.begin(115200);
  // while (analogRead(startPin) <= 900) {
  //   printCounter++;
  //   if (printCounter%100 == 0)
  //     Serial.println("Waiting to start");
  // }
  // delay(5000);
  Serial.println("Started");
}

void loop() {
  // pullSensors();
  // ws->clean_sensors();
  pullSensors(); 
  avgs = ws->get_sensors_avg();
  if (dips[0] == 0) {
    algo->selectMode();  
    // Serial.println("Normal");
  }
  else {
    algo->spin();
    // Serial.println("Spinnn");
  }
  writeMotors();
  // debug();
}

void pullSensors() {
  ir_sensors[0] = digitalRead(leftSideSensor);
  ir_sensors[1] = digitalRead(leftSensor);
  ir_sensors[2] = digitalRead(middleSensor);
  ir_sensors[3] = digitalRead(rightSensor);
  ir_sensors[4] = digitalRead(rightSideSensor);
  currentMillis = millis();
  line_sensors[0] = analogRead(leftLineSensor);
  line_sensors[1] = analogRead(rightLineSensor);
  dips[0] = digitalRead(dip1);
  dips[1] = digitalRead(dip2);
  Serial.println(dips[0]);
}

void debug() {
  printCounter++;
  if (printCounter % 100 == 0) {
    debugLine();
    debugAverages();
    // debugLineLP(ws->line_check());
    // debugEnemy(ws->enemy_pos());
    Serial.println();
  }
}

void writeMotors() {
  motors[0] = motors[0]/1.65;
  motors[1] = motors[1]/1.65;
  if (motors[0] > 0) {
    analogWrite(leftF, abs(motors[0]));
    analogWrite(leftB, 0);
  }
  else if (motors[0] < 0) {
    analogWrite(leftB, abs(motors[0]));
    analogWrite(leftF, 0);
  }
  else {
    analogWrite(leftF, 255);
    analogWrite(leftB, 255);
  }
  if (motors[1] > 0) {
    analogWrite(rightF, abs(motors[1]));
    analogWrite(rightB, 0);
  }
  else if (motors[1] < 0) {
    analogWrite(rightB, abs(motors[1]));
    analogWrite(rightF, 0);
  }
  else {
    analogWrite(rightF, 255);
    analogWrite(rightB, 255);
  }
}

double writeServo(int pin, double deg) {

  double p = 2.038;

  if (deg > 179) {

    deg = 179;

  } 

  if (deg < 30.355) {

    deg = 30.355;

  }

  double ht = deg * p / 180;

  double dc = ht / p;

  double invertedDc = 1 - dc;

  analogWrite(pin, invertedDc * 255);

  return dc;

}

void debugEnemy(EnemyPosition ep){
  switch(ep) {
    case NONE:     Serial.print("NONE"); break;
    case LEFT:     Serial.print("LEFT"); break;
    case FRONT:    Serial.print("FRONT"); break;
    case RIGHT:    Serial.print("RIGHT"); break;
    case MIDLEFT:  Serial.print("MIDLEFT"); break;
    case MIDRIGHT: Serial.print("MIDRIGHT"); break;
    case FARFRONT: Serial.print("FARFRONT"); break;
  }
  Serial.println();
}

void debugLineLP(LinePosition lp) {
  switch(lp) {
    case OFF_LINE: Serial.println("OFF LINE "); break;
    case LEFT_LINE: Serial.println("LEFT LINE "); break;
    case RIGHT_LINE: Serial.println("RIGHT LINE "); break;
    case CENTER_LINE: Serial.println("CENTER LINE "); break;
  }
}

void debugLine(){
  for(int i = 0; i < 2; i++){
    Serial.print(line_sensors[i]);
    Serial.print(" ");
  }
}

void debugIR(){
  for(int i = 0; i < 5; i++){
    Serial.print(ir_sensors[i]);
    Serial.print(" ");
  }
}

void debugDIP(){
  Serial.print(digitalRead(dip1));
  Serial.print(" ");
  Serial.print(digitalRead(dip2));
  Serial.print(" ");
}

void debugAverages() {
  for(int i = 0; i < 5; i++){
    Serial.print(avgs[i]);
    Serial.print(" ");
  }
}