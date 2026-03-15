#include <Arduino.h>
#include "world_state.hpp"
#include "motor_actions.hpp"
#include "timer.hpp"
#include <Adafruit_MPU6050.h> // Include the Adafruit MPU6050 library
#include <Adafruit_Sensor.h>  // Include the Adafruit Unified Sensor library
#include <Adafruit_SSD1306.h>
#include <Wire.h>
#include "Algorithms.hpp"
#include <Servo.h>


Servo robotServo;
const int leftSideSensor = PA2;
const int leftSensor = PA3;
const int middleSensor = PA4;
const int rightSensor = PA5;
const int rightSideSensor = PA6;

const int rightB = PB6;
const int rightF = PB7;
const int leftF = PA8;
const int leftB = PA9;

const int screenSCL = PB8;
const int screenSDA = PB9; 

const int startPin = PB10;
const int leftLineSensor = PA7;
const int rightLineSensor = PB0;

const int imuSCL = PB8;
const int imuSDA = PB9;

const int servoPin = PA0;

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
static unsigned long servo_start_time = 0;

// Declare MPU6050 object
Adafruit_MPU6050 mpu;

sensors_event_t accel, gyro, temp;
void pullSensors();
void writeMotors();
void debug();
void debugLine();
void debugLineLP(LinePosition lp);
void debugIR();
void debugAverages();
void writeServo(int pin, double deg);
void debugEnemy(EnemyPosition ep);
void setLED();
template <typename T>

void aliFunc(const T& value) {
  if (dips[2] == LOW) {
    Serial.print(value);
  }
}
template <typename T>
void aliFuncln(const T& value) {
  if (dips[2] == LOW) {
    Serial.println(value);
  }
}

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
  pinMode(dip3, INPUT_PULLUP);
  pinMode(pushButton, INPUT);
  pinMode(0, OUTPUT);

  Serial.begin(9600);
  aliFuncln("Initializing...");

  // Initialize MPU6050
  Wire.setSCL(imuSCL);
  Wire.setSDA(imuSDA);
  Wire.begin(imuSDA, imuSCL); // Initialize I2C for MPU6050
  aliFuncln("Adafruit MPU6050 test!");

  // Try to initialize MPU6050!
  if (!mpu.begin()) {
    aliFuncln("Failed to find MPU6050 chip");
    while (1) {
      delay(10);
    }
  }
  aliFuncln("MPU6050 Found!");

  robotServo.attach(servoPin);

  mpu.setAccelerometerRange(MPU6050_RANGE_8_G);
  mpu.setGyroRange(MPU6050_RANGE_500_DEG);
  mpu.setFilterBandwidth(MPU6050_BAND_21_HZ);
  // while (analogRead(startPin) <= 900) {
  //   printCounter++;
  //   if (printCounter%100 == 0)
  //     aliFuncln("Waiting to start");
  // }
  // delay(5000);
  servo_start_time = millis(); // Record the start time for the servo action
  aliFuncln("Started");
}

void loop() {
  pullSensors(); 
  setLED();
  
  // if((currentMillis - servo_start_time) < 10000){
  //   writeServo(servoPin, 90);
  // }

  writeServo(servoPin, 90);
  
  if (dips[0] == 0) {
    algo->selectMode();  
  }
  else {
    algo->spin();
  }
  writeMotors();
  debug();
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
  dips[2] = digitalRead(dip3);
  mpu.getEvent(&accel, &gyro, &temp);
}
void setLED(){
  digitalWrite(led1Pin, line_sensors[0] < 200); // change these later when needed
  digitalWrite(led2Pin, line_sensors[1] < 200);
}
void debug() {
  printCounter++;
  if (printCounter % 25 == 0) {
    aliFunc("Accel X: ");
    aliFunc(accel.acceleration.x);
    aliFunc(" Y: ");
    aliFunc(accel.acceleration.y);
    aliFunc(" Z: ");
    aliFuncln(accel.acceleration.z);
    debugLine();
    debugAverages();
    // debugLineLP(ws->line_check());
    // debugEnemy(ws->enemy_pos());
    aliFuncln("");
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

void writeServo(int pin, double deg) {
  // Constrain the degree to a valid range (0-180 for standard servos)
  if (deg < 0) {
    deg = 0;
  }
  if (deg > 180) {
    deg = 180;
  }

  // Map the degree to a pulse width in microseconds
  // Standard servo pulse widths: 1000us for 0 deg, 1500us for 90 deg, 2000us for 180 deg
  long pulse_width_us = map(deg, 0, 180, 1000, 2000);

  // Handle signal inversion: To get a pulse of 'pulse_width_us' after an external inverter,
  // we must output HIGH for the remainder of the 20ms (20000us) period.

  robotServo.writeMicroseconds(pulse_width_us);
}

void debugEnemy(EnemyPosition ep){
  switch(ep) {
    case NONE:     aliFunc("NONE"); break;
    case LEFT:     aliFunc("LEFT"); break;
    case FRONT:    aliFunc("FRONT"); break;
    case RIGHT:    aliFunc("RIGHT"); break;
    case MIDLEFT:  aliFunc("MIDLEFT"); break;
    case MIDRIGHT: aliFunc("MIDRIGHT"); break;
    case FARFRONT: aliFunc("FARFRONT"); break;
  }
  aliFuncln("");
}

void debugLineLP(LinePosition lp) {
  switch(lp) {
    case OFF_LINE: aliFuncln("OFF LINE "); break;
    case LEFT_LINE: aliFuncln("LEFT LINE "); break;
    case RIGHT_LINE: aliFuncln("RIGHT LINE "); break;
    case CENTER_LINE: aliFuncln("CENTER LINE "); break;
  }
}

void debugLine(){
  for(int i = 0; i < 2; i++){
    aliFunc(line_sensors[i]);
    aliFunc(" ");
  }
}

void debugIR(){
  for(int i = 0; i < 5; i++){
    aliFunc(ir_sensors[i]);
    aliFunc(" ");
  }
}

void debugDIP(){
  aliFunc(digitalRead(dip1));
  aliFunc(" ");
  aliFunc(digitalRead(dip2));
  aliFunc(" ");
}

void debugAverages() {
  for(int i = 0; i < 5; i++){
    aliFunc(avgs[i]);
    aliFunc(" ");
  }
}