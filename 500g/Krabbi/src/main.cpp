#include <Arduino.h>
#include "world_state.hpp"
#include "motor_actions.hpp"
#include "timer.hpp"
#include <Adafruit_MPU6050.h> // Include the Adafruit MPU6050 library
#include <Adafruit_Sensor.h>  // Include the Adafruit Unified Sensor library
#include <Adafruit_SSD1306.h>
#include <Wire.h>
#include "Algorithms.hpp"
#include <MadgwickAHRS.h>
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
const unsigned long startupDelayMs = 5000;

long currentMillis = 0;
int printCounter = 0;
int zCounter = 0;
bool playing = true;

unsigned long lastGyroMicros = 0;
float rollDeg = 0.0f;
float pitchDeg = 0.0f;
float yawDeg = 0.0f;
float yawScaleFactor = 360.0f / 365.0f;
float yawOffsetDeg = 0.0f;
float correctedYawDeg = 0.0f;
bool yawOffsetInitialized = false;
float linearAccelX = 0.0f;
float linearAccelY = 0.0f;
float linearAccelZ = 0.0f;
float robotAccelX = 0.0f;
float robotAccelY = 0.0f;
float robotAccelZ = 0.0f;
float robotGyroX = 0.0f;
float robotGyroY = 0.0f;
float robotGyroZ = 0.0f;
float gyroBiasX = 0.0f;
float gyroBiasY = 0.0f;
float gyroBiasZ = 0.0f;
float calibratedGravityMagnitude = SENSORS_GRAVITY_STANDARD;
float imuMountYawDeg = 0.0f;
float imuToRobot[3][3] = {
  {1.0f, 0.0f, 0.0f},
  {0.0f, 1.0f, 0.0f},
  {0.0f, 0.0f, 1.0f}
};

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
Madgwick filter;

sensors_event_t accel, gyro, temp;
void calibrateImuMounting();
void buildImuToRobotTransform(float gravityX, float gravityY, float gravityZ);
float normalizeAngleDeg(float angleDeg);
void rotateIntoRobotFrame(float inputX, float inputY, float inputZ, float& outputX, float& outputY, float& outputZ);
void pullSensors();
void updateOrientation();
void writeServo(int pin, double deg);
void setLED();
void writeMotors();
void debug();
void debugLine();
void debugLineLP(LinePosition lp);
void debugIR();
void debugAverages();
void debugEnemy(EnemyPosition ep);
void debugDIP();
void debugIMU();
void debugFusedValues();

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
  pinMode(led1Pin, OUTPUT);
  pinMode(led2Pin, OUTPUT);

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
  unsigned long startupDelayStart = millis();
  aliFuncln("Hold robot still during startup delay");
  calibrateImuMounting();
  filter.begin(375.0f);
  unsigned long startupElapsed = millis() - startupDelayStart;
  if (startupElapsed < startupDelayMs) {
    delay(startupDelayMs - startupElapsed);
  }
  servo_start_time = millis(); // Record the start time for the servo action
  lastGyroMicros = micros();
  aliFuncln("Started");
}

void loop() {
  pullSensors(); 
  updateOrientation();
  setLED();
  avgs = ws->get_sensors_avg();

  if (dips[0] == LOW) {
    algo->selectMode();  
  }
  else {
    algo->spin();
  }
  if (!playing) {
    motors[0] = 0;
    motors[1] = 0;
    writeServo(servoPin, 0);
  }
  else {
    writeServo(servoPin, 90);
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

  rotateIntoRobotFrame(
    accel.acceleration.x,
    accel.acceleration.y,
    accel.acceleration.z,
    robotAccelX,
    robotAccelY,
    robotAccelZ
  );

  rotateIntoRobotFrame(
    gyro.gyro.x - gyroBiasX,
    gyro.gyro.y - gyroBiasY,
    gyro.gyro.z - gyroBiasZ,
    robotGyroX,
    robotGyroY,
    robotGyroZ
  );
}

void updateOrientation() {
  unsigned long nowMicros = micros();
  float dt = (nowMicros - lastGyroMicros) / 1000000.0f;
  lastGyroMicros = nowMicros;

  if (dt <= 0.0f) {
    return;
  }

  filter.begin(1.0f / dt);
  filter.updateIMU(
    robotGyroX * RAD_TO_DEG,
    robotGyroY * RAD_TO_DEG,
    robotGyroZ * RAD_TO_DEG,
    robotAccelX / calibratedGravityMagnitude,
    robotAccelY / calibratedGravityMagnitude,
    robotAccelZ / calibratedGravityMagnitude
  );

  rollDeg = filter.getRoll();
  pitchDeg = filter.getPitch();
  yawDeg = filter.getYaw();
  if (!yawOffsetInitialized) {
    yawOffsetDeg = yawDeg;
    yawOffsetInitialized = true;
  }
  correctedYawDeg = normalizeAngleDeg((yawDeg - yawOffsetDeg) * yawScaleFactor);

  float rollRad = rollDeg * DEG_TO_RAD;
  float pitchRad = pitchDeg * DEG_TO_RAD;
  float gravityX = -calibratedGravityMagnitude * sinf(pitchRad);
  float gravityY = calibratedGravityMagnitude * sinf(rollRad) * cosf(pitchRad);
  float gravityZ = calibratedGravityMagnitude * cosf(rollRad) * cosf(pitchRad);

  linearAccelX = robotAccelX - gravityX;
  linearAccelY = robotAccelY - gravityY;
  linearAccelZ = robotAccelZ - gravityZ;
}

void calibrateImuMounting() {
  const int calibrationSamples = 300;
  float accelSumX = 0.0f;
  float accelSumY = 0.0f;
  float accelSumZ = 0.0f;
  float gyroSumX = 0.0f;
  float gyroSumY = 0.0f;
  float gyroSumZ = 0.0f;

  aliFuncln("Calibrating IMU...");

  for (int i = 0; i < calibrationSamples; i++) {
    mpu.getEvent(&accel, &gyro, &temp);
    accelSumX += accel.acceleration.x;
    accelSumY += accel.acceleration.y;
    accelSumZ += accel.acceleration.z;
    gyroSumX += gyro.gyro.x;
    gyroSumY += gyro.gyro.y;
    gyroSumZ += gyro.gyro.z;
    delay(5);
  }

  gyroBiasX = gyroSumX / calibrationSamples;
  gyroBiasY = gyroSumY / calibrationSamples;
  gyroBiasZ = gyroSumZ / calibrationSamples;
  calibratedGravityMagnitude = sqrtf(
    sq(accelSumX / calibrationSamples) +
    sq(accelSumY / calibrationSamples) +
    sq(accelSumZ / calibrationSamples)
  );

  buildImuToRobotTransform(
    accelSumX / calibrationSamples,
    accelSumY / calibrationSamples,
    accelSumZ / calibrationSamples
  );
}

void buildImuToRobotTransform(float gravityX, float gravityY, float gravityZ) {
  float gravityMag = sqrtf((gravityX * gravityX) + (gravityY * gravityY) + (gravityZ * gravityZ));
  if (gravityMag <= 0.0f) {
    return;
  }

  float sourceX = gravityX / gravityMag;
  float sourceY = gravityY / gravityMag;
  float sourceZ = gravityZ / gravityMag;
  float targetX = 0.0f;
  float targetY = 0.0f;
  float targetZ = 1.0f;

  float crossX = (sourceY * targetZ) - (sourceZ * targetY);
  float crossY = (sourceZ * targetX) - (sourceX * targetZ);
  float crossZ = (sourceX * targetY) - (sourceY * targetX);
  float crossMag = sqrtf((crossX * crossX) + (crossY * crossY) + (crossZ * crossZ));
  float dot = (sourceX * targetX) + (sourceY * targetY) + (sourceZ * targetZ);

  float alignment[3][3] = {
    {1.0f, 0.0f, 0.0f},
    {0.0f, 1.0f, 0.0f},
    {0.0f, 0.0f, 1.0f}
  };

  if (crossMag > 1e-6f) {
    float axisX = crossX / crossMag;
    float axisY = crossY / crossMag;
    float axisZ = crossZ / crossMag;
    float angle = acosf(constrain(dot, -1.0f, 1.0f));
    float c = cosf(angle);
    float s = sinf(angle);
    float oneMinusC = 1.0f - c;

    alignment[0][0] = c + (axisX * axisX * oneMinusC);
    alignment[0][1] = (axisX * axisY * oneMinusC) - (axisZ * s);
    alignment[0][2] = (axisX * axisZ * oneMinusC) + (axisY * s);
    alignment[1][0] = (axisY * axisX * oneMinusC) + (axisZ * s);
    alignment[1][1] = c + (axisY * axisY * oneMinusC);
    alignment[1][2] = (axisY * axisZ * oneMinusC) - (axisX * s);
    alignment[2][0] = (axisZ * axisX * oneMinusC) - (axisY * s);
    alignment[2][1] = (axisZ * axisY * oneMinusC) + (axisX * s);
    alignment[2][2] = c + (axisZ * axisZ * oneMinusC);
  }
  else if (dot < 0.0f) {
    alignment[1][1] = -1.0f;
    alignment[2][2] = -1.0f;
  }

  float yawRad = imuMountYawDeg * DEG_TO_RAD;
  float yawRotation[3][3] = {
    {cosf(yawRad), -sinf(yawRad), 0.0f},
    {sinf(yawRad),  cosf(yawRad), 0.0f},
    {0.0f,          0.0f,         1.0f}
  };

  for (int row = 0; row < 3; row++) {
    for (int col = 0; col < 3; col++) {
      imuToRobot[row][col] =
        (yawRotation[row][0] * alignment[0][col]) +
        (yawRotation[row][1] * alignment[1][col]) +
        (yawRotation[row][2] * alignment[2][col]);
    }
  }
}

float normalizeAngleDeg(float angleDeg) {
  while (angleDeg > 180.0f) {
    angleDeg -= 360.0f;
  }
  while (angleDeg <= -180.0f) {
    angleDeg += 360.0f;
  }
  return angleDeg;
}

void rotateIntoRobotFrame(float inputX, float inputY, float inputZ, float& outputX, float& outputY, float& outputZ) {
  outputX =
    (imuToRobot[0][0] * inputX) +
    (imuToRobot[0][1] * inputY) +
    (imuToRobot[0][2] * inputZ);
  outputY =
    (imuToRobot[1][0] * inputX) +
    (imuToRobot[1][1] * inputY) +
    (imuToRobot[1][2] * inputZ);
  outputZ =
    (imuToRobot[2][0] * inputX) +
    (imuToRobot[2][1] * inputY) +
    (imuToRobot[2][2] * inputZ);
}

void setLED(){
  digitalWrite(led1Pin, line_sensors[0] < 200); // change these later when needed
  digitalWrite(led2Pin, line_sensors[1] < 200);
}

void debug() {
  printCounter++;
  if (printCounter % 25 == 0) {
    debugAverages();
    debugDIP();
    debugFusedValues();
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

void debugDIP() {
  aliFuncln(" ");
  aliFunc(digitalRead(dip1));
  aliFunc(" ");
  aliFunc(digitalRead(dip2));
  aliFunc(" ");
  aliFunc(digitalRead(dip3));
  aliFuncln(" ");
}

void debugAverages() {
  for(int i = 0; i < 5; i++){
    aliFunc(avgs[i]);
    aliFunc(" ");
  }
}

void debugIMU() {
  aliFunc("Robot Accel X: ");
  aliFunc(robotAccelX);
  aliFunc(" Y: ");
  aliFunc(robotAccelY);
  aliFunc(" Z: ");
  aliFuncln(robotAccelZ);
  aliFunc("Robot Gyro X: ");
  aliFunc(robotGyroX);
  aliFunc(" Y: ");
  aliFunc(robotGyroY);
  aliFunc(" Z: ");
  aliFuncln(robotGyroZ);
}

void debugFusedValues() {
    aliFuncln("Roll/Pitch/Yaw: " + String(rollDeg) + " " + String(pitchDeg) + " " + String(correctedYawDeg));
    aliFuncln("Linear Accel XYZ: " + String(linearAccelX) + " " + String(linearAccelY) + " " + String(linearAccelZ));
}