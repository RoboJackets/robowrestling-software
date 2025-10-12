#include <Arduino.h>
#include "world_state.hpp"
#include "motor_actions.hpp"
#include "timer.hpp"
#include "Algorithms.hpp"

const int leftSensor = 2;
const int middleSensor = 3;
const int rightSensor = 4;

const int rightB = 6;
const int rightF = 5;
const int leftB = 8;
const int leftF = 7;

const int startPin = 0;
const int leftLineSensor= 23;
const int rightLIneSensor= 22;

long currentMillis = 0;
int printCounter = 0;

float* avgs;
int motors[2] = {0};
int line_sensors[2] = {0};
int ir_sensors[3] = {0};

timer* algo_timer = new timer(&currentMillis);
world_state* ws = new world_state(line_sensors, ir_sensors);
motor_actions* ma = new motor_actions(motors);
algorithms* algo = new algorithms(ma, ws, algo_timer);


void drive();
void pullSensors();
void writeMotors();
void debug();
void debugLine();
void debugIR();
void debugAverages();
void debugEnemy(EnemyPosition ep);

void setup() {
  pinMode(leftSensor, INPUT);
  pinMode(middleSensor, INPUT);
  pinMode(rightSensor, INPUT);
  pinMode(startPin, INPUT);

  pinMode(rightF, OUTPUT);
  pinMode(rightB, OUTPUT);
  pinMode(leftF, OUTPUT);
  pinMode(leftB, OUTPUT);

  pinMode(leftLineSensor, INPUT);
  pinMode(rightLIneSensor, INPUT);

  Serial.begin(9600);
  // while (digitalRead(startPin) == 0) {
  //   printCounter++;
  //   if (printCounter%100000 == 0)
  //     Serial.println("Waiting to start");
  // }
}

void loop() {
  // while (digitalRead(startPin) == 0) {
  //   printCounter++;
  //   if (printCounter%100000 == 0)
  //     Serial.println("Waiting to start");
  // }
  pullSensors();
  ws->clean_sensors();
  avgs = ws->get_sensors_avg();
  algo->defaultBehavior();  
  writeMotors();
  debug();
}

void pullSensors() {
  ir_sensors[0] = digitalRead(leftSensor);
  ir_sensors[1] = digitalRead(middleSensor);
  ir_sensors[2] = digitalRead(rightSensor);
  currentMillis = millis();
  line_sensors[0] = analogRead(leftLineSensor);
  line_sensors[1] = analogRead(rightLIneSensor);
}

void debug() {
  printCounter++;
  if (printCounter % 10000 == 0) {
    debugLine();
    debugAverages();
    Serial.println();
  }
}

void writeMotors() {
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
void debugLine(){
  for(int i = 0; i < 2; i++){
    Serial.print(line_sensors[i]);
    Serial.print(" ");
  }
}

void debugIR(){
  for(int i = 0; i < 3; i++){
    Serial.print(ir_sensors[i]);
    Serial.print(" ");
  }
}

void debugAverages(){
  for(int i = 0; i < 3; i++){
    Serial.print(avgs[i]);
    Serial.print(" ");
  }
}