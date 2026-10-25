#include <Arduino.h>
#include "world_state.hpp"
#include "motor_actions.hpp"
#include "timer.hpp"
#include <Adafruit_MPU6050.h> 
#include <Adafruit_Sensor.h>  
#include <Wire.h>
#include "Algorithms.hpp"
#include <MadgwickAHRS.h>
#include <Servo.h> 

Servo robotServo; 

// Sensor and Motor Pins
const int leftSideSensor = PA2;
const int leftSensor = PA3;
const int middleSensor = PA4;
const int rightSensor = PA5;
const int rightSideSensor = PA6;

const int rightB = PB6;
const int rightF = PB7;
const int leftF = PA8;
const int leftB = PA9;

const int startPin = PB10;
const int leftLineSensor = PA7; 
const int rightLineSensor = PB15;

const int imuSCL = PB8;
const int imuSDA = PB9;
const int servoPin = PA0; 

const int led1Pin = PB5;
const int led2Pin = PB1;

const int dip1 = PB12;
const int dip2 = PB13;
const int dip3 = PB14;

// State Variables
bool motorsEnabled = true; // Set false to disable drive motors for sensor testing.
const unsigned long startupDelayMs = 0;
const int START_MODULE_ACTIVE_STATE = HIGH;
long currentMillis = 0;
int printCounter = 0; // RESTORED
bool startupDelayComplete = false;
bool startSignalReceived = false;
bool imuCalibrationDone = false;

// IMU Tracking 
static unsigned long lastImuMicros = 0;
const unsigned long IMU_INTERVAL_MICROS = 2500; // 400Hz
const int IMU_CALIBRATION_SAMPLES = 80;
const unsigned long IMU_CALIBRATION_SAMPLE_DELAY_MS = 1;
unsigned long lastGyroMicros = 0;
float linearAccelX = 0.0f, linearAccelY = 0.0f, linearAccelZ = 0.0f;
float robotAccelX = 0.0f, robotAccelY = 0.0f, robotAccelZ = 0.0f;
float robotGyroX = 0.0f, robotGyroY = 0.0f, robotGyroZ = 0.0f;
float gyroBiasX = 0.0f, gyroBiasY = 0.0f, gyroBiasZ = 0.0f;
float calibratedGravityMagnitude = SENSORS_GRAVITY_STANDARD;
float imuToRobot[3][3] = { {1, 0, 0}, {0, 1, 0}, {0, 0, 1} };
float rollDeg = 0.0f, pitchDeg = 0.0f; // RESTORED for debug prints

// Collision Thresholds & Filtering
bool useMadgwickFilter = true; 
float lastAccelMagnitude = 0.0f;
const float impactThreshold = 4.0f; 
bool impactOccurred = false; 
float kalmanForwardAccelEstimate = 0.0f;
float kalmanForwardAccelCovariance = 1.0f;
const float kalmanProcessNoise = 0.08f;
const float kalmanMeasurementNoise = 0.9f;

int motors[2] = {0};
int dips[3] = {0};
int line_sensors[2] = {0};
int ir_sensors[5] = {0};

timer last_enemy_changed(&currentMillis);
timer behavior_timer(&currentMillis);
timer startup_delay_timer(&currentMillis);
world_state ws(line_sensors, ir_sensors);
motor_actions ma(motors);
algorithms algo(ma, ws, behavior_timer, last_enemy_changed);

Adafruit_MPU6050 mpu;
Madgwick filter;
sensors_event_t accel, gyro, temp;

// Function Prototypes
void calibrateImuMounting();
void buildImuToRobotTransform(float gravityX, float gravityY, float gravityZ);
void rotateIntoRobotFrame(float inputX, float inputY, float inputZ, float& outputX, float& outputY, float& outputZ);
void pullSensors();
void updateIMU();
void updateOrientation();
void writeMotors();
void writeServo(int pin, double deg); 
void setLED();
bool detectImuImpact();

// RESTORED: Debug Function Prototypes
void debug();
void debugLine();
void debugIR();
void debugAverages();
void debugDIP();
void debugFusedValues();
void debugEnemy(EnemyPosition ep);

// RESTORED: Custom Print Templates (Only prints if Dip 3 is LOW)
template <typename T>
void aliFunc(const T& value) {
  if (dips[2] == LOW) Serial.print(value);
}
template <typename T>
void aliFuncln(const T& value) {
  if (dips[2] == LOW) Serial.println(value);
}

// Smooths noisy accelerometer data to detect genuine hard impacts
float applyKalmanForwardAccel(float measurement) {
  kalmanForwardAccelCovariance += kalmanProcessNoise;
  float kalmanGain = kalmanForwardAccelCovariance / (kalmanForwardAccelCovariance + kalmanMeasurementNoise);
  kalmanForwardAccelEstimate += kalmanGain * (measurement - kalmanForwardAccelEstimate);
  kalmanForwardAccelCovariance = (1.0f - kalmanGain) * kalmanForwardAccelCovariance;
  return kalmanForwardAccelEstimate;
}

// Monitors filtered IMU acceleration to flag opponent collisions
bool detectImuImpact() {
  float accelMagnitudeSmoothed = applyKalmanForwardAccel(linearAccelX);
  lastAccelMagnitude = accelMagnitudeSmoothed;
  return (accelMagnitudeSmoothed < -impactThreshold);
}

void setup() {
  //Serial.begin(115200); // Added to ensure your debug prints actually show up
  currentMillis = millis();
  // startup_delay_timer.reset();
  // startup_delay_timer.setTarget(startupDelayMs);

  pinMode(leftSensor, INPUT);
  pinMode(middleSensor, INPUT);
  pinMode(rightSensor, INPUT);
  pinMode(leftSideSensor, INPUT);
  pinMode(rightSideSensor, INPUT);
  pinMode(startPin, INPUT_PULLDOWN);

  pinMode(rightF, OUTPUT);
  pinMode(rightB, OUTPUT);
  pinMode(leftF, OUTPUT);
  pinMode(leftB, OUTPUT);

  pinMode(leftLineSensor, INPUT_PULLUP);
  pinMode(rightLineSensor, INPUT_PULLUP);
  pinMode(dip1, INPUT_PULLUP);
  pinMode(dip2, INPUT_PULLUP);
  pinMode(dip3, INPUT_PULLUP);
  pinMode(led1Pin, OUTPUT);
  pinMode(led2Pin, OUTPUT);

  Wire.setSCL(imuSCL);
  Wire.setSDA(imuSDA);
  Wire.begin(imuSDA, imuSCL); 

  if (!mpu.begin()) while (1) delay(10);

  // Initialize Servo
  robotServo.writeMicroseconds(1000); 
  robotServo.attach(servoPin);
  writeServo(servoPin, 0); 

  mpu.setAccelerometerRange(MPU6050_RANGE_8_G);
  mpu.setGyroRange(MPU6050_RANGE_500_DEG);
  mpu.setFilterBandwidth(MPU6050_BAND_21_HZ);

  calibrateImuMounting();
  imuCalibrationDone = true;

  filter.begin(400.0f);  
  lastGyroMicros = micros();
  // aliFuncln("Started");
}

void loop() {
  pullSensors(); 
  currentMillis = millis();

  bool testMode = (dips[2] == LOW);
  bool startModuleActive = (digitalRead(startPin) == START_MODULE_ACTIVE_STATE);

  // Safety Gate: Disable everything if the start module is off
  if (startModuleActive) {
      // Pre-match / Startup Logic
    if (testMode) {
      startSignalReceived = true;
      startupDelayComplete = true;
    } else {
      if (!startSignalReceived) {
        startSignalReceived = true;
        startupDelayComplete = false;
        startup_delay_timer.reset();
        startup_delay_timer.start();
        startup_delay_timer.setTarget(startupDelayMs);
      }

      if (!startup_delay_timer.isFinished()) {
        motors[0] = 0;
        motors[1] = 0;
        writeServo(servoPin, 0); 
        writeMotors();
        return;
      }
      startupDelayComplete = true;
    }
    
    // High-Frequency IMU Polling
    if (micros() - lastImuMicros >= IMU_INTERVAL_MICROS) {
      lastImuMicros = micros();
      updateIMU();
      updateOrientation();
    }

    setLED();
    ws.get_sensors_avg();

    EnemyPosition enemyPos = ws.enemy_pos();
    LinePosition linePos = ws.line_check();
    
    // Collision Trigger Logic
    bool enemyInPushingArc = (enemyPos == FRONT || enemyPos == FRONT_LEFT || enemyPos == FRONT_RIGHT || enemyPos == MIDLEFT || enemyPos == MIDRIGHT || enemyPos == FARFRONT);
    bool imuImpactArmed = (linePos == OFF_LINE) && enemyInPushingArc;
    bool impactJustHappened = detectImuImpact(); 

    if (!impactOccurred && imuImpactArmed && impactJustHappened) {
      impactOccurred = true;
      algo.setFullChargeMode(true);
    }

    if (impactOccurred && !algo.isFullChargeMode()) {
      impactOccurred = false;
      digitalWrite(led1Pin, LOW);
      digitalWrite(led2Pin, LOW);
    } else if (impactOccurred) {
      digitalWrite(led1Pin, HIGH);
      digitalWrite(led2Pin, HIGH);
    }

    // Execute Core Driving Behaviors
    algo.selectMode(linearAccelX, dips[0], dips[1], 0.0f);
    
    writeServo(servoPin, 250); 
    writeMotors();
    
    // RESTORED: Fire debug prints
    debug();
  } else {
    startSignalReceived = false;
    startupDelayComplete = false;
    startup_delay_timer.reset();
    impactOccurred = false;
    algo.resetState();
    algo.setFullChargeMode(false);
    digitalWrite(led1Pin, LOW);
    digitalWrite(led2Pin, LOW);
    motors[0] = 0;
    motors[1] = 0;
    writeServo(servoPin, 0); 
    writeMotors();
    return;
  }
}

void pullSensors() {
  ir_sensors[0] = digitalRead(leftSideSensor);
  ir_sensors[1] = digitalRead(leftSensor);
  ir_sensors[2] = digitalRead(middleSensor);
  ir_sensors[3] = digitalRead(rightSensor);
  ir_sensors[4] = digitalRead(rightSideSensor);
  
  int rightReads = digitalRead(rightLineSensor) + digitalRead(rightLineSensor) +digitalRead(rightLineSensor);
  int leftReads = digitalRead(leftLineSensor) + digitalRead(leftLineSensor) +digitalRead(leftLineSensor);
  line_sensors[0] = (leftReads < 1) ? LOW : HIGH;
  line_sensors[1] = (rightReads < 1) ? LOW : HIGH;
  
  dips[0] = digitalRead(dip1);
  dips[1] = digitalRead(dip2);
  dips[2] = digitalRead(dip3);
}

void updateIMU() {
  mpu.getEvent(&accel, &gyro, &temp);

  rotateIntoRobotFrame(
    accel.acceleration.x, accel.acceleration.y, accel.acceleration.z,
    robotAccelX, robotAccelY, robotAccelZ
  );

  rotateIntoRobotFrame(
    gyro.gyro.x - gyroBiasX, gyro.gyro.y - gyroBiasY, gyro.gyro.z - gyroBiasZ,
    robotGyroX, robotGyroY, robotGyroZ
  );
}

void updateOrientation() {
  unsigned long nowMicros = micros();
  float dt = (nowMicros - lastGyroMicros) / 1000000.0f;
  lastGyroMicros = nowMicros;

  if (dt <= 0.0f) return;

  if (useMadgwickFilter) {
      filter.updateIMU(
        robotGyroX * RAD_TO_DEG, robotGyroY * RAD_TO_DEG, robotGyroZ * RAD_TO_DEG,
        robotAccelX / calibratedGravityMagnitude, robotAccelY / calibratedGravityMagnitude, robotAccelZ / calibratedGravityMagnitude
      );

      rollDeg = filter.getRoll(); // Tracked for debug
      pitchDeg = filter.getPitch(); // Tracked for debug
      
      float rollRad = rollDeg * DEG_TO_RAD;
      float pitchRad = pitchDeg * DEG_TO_RAD;
      float gravityX = -calibratedGravityMagnitude * sinf(pitchRad);
      float gravityY = calibratedGravityMagnitude * sinf(rollRad) * cosf(pitchRad);
      float gravityZ = calibratedGravityMagnitude * cosf(rollRad) * cosf(pitchRad);

      linearAccelX = robotAccelX - gravityX;
      linearAccelY = robotAccelY - gravityY;
      linearAccelZ = robotAccelZ - gravityZ;
  } else {
      linearAccelX = robotAccelX;
      linearAccelY = robotAccelY;
      linearAccelZ = robotAccelZ;
  }
}

void calibrateImuMounting() {
  float accelSumX = 0, accelSumY = 0, accelSumZ = 0;
  float gyroSumX = 0, gyroSumY = 0, gyroSumZ = 0;

  aliFuncln("Calibrating IMU...");

  for (int i = 0; i < IMU_CALIBRATION_SAMPLES; i++) {
    mpu.getEvent(&accel, &gyro, &temp);
    accelSumX += accel.acceleration.x; accelSumY += accel.acceleration.y; accelSumZ += accel.acceleration.z;
    gyroSumX += gyro.gyro.x; gyroSumY += gyro.gyro.y; gyroSumZ += gyro.gyro.z;
    if (IMU_CALIBRATION_SAMPLE_DELAY_MS > 0) {
      delay(IMU_CALIBRATION_SAMPLE_DELAY_MS);
    }
  }

  gyroBiasX = gyroSumX / IMU_CALIBRATION_SAMPLES;
  gyroBiasY = gyroSumY / IMU_CALIBRATION_SAMPLES;
  gyroBiasZ = gyroSumZ / IMU_CALIBRATION_SAMPLES;
  calibratedGravityMagnitude = sqrtf(sq(accelSumX / IMU_CALIBRATION_SAMPLES) + sq(accelSumY / IMU_CALIBRATION_SAMPLES) + sq(accelSumZ / IMU_CALIBRATION_SAMPLES));

  buildImuToRobotTransform(accelSumX / IMU_CALIBRATION_SAMPLES, accelSumY / IMU_CALIBRATION_SAMPLES, accelSumZ / IMU_CALIBRATION_SAMPLES);
}

void buildImuToRobotTransform(float gravityX, float gravityY, float gravityZ) {
  float gravityMag = sqrtf((gravityX * gravityX) + (gravityY * gravityY) + (gravityZ * gravityZ));
  if (gravityMag <= 0.0f) return;

  float sourceX = gravityX / gravityMag; float sourceY = gravityY / gravityMag; float sourceZ = gravityZ / gravityMag;
  float targetX = 0.0f, targetY = 0.0f, targetZ = 1.0f;

  float crossX = (sourceY * targetZ) - (sourceZ * targetY);
  float crossY = (sourceZ * targetX) - (sourceX * targetZ);
  float crossZ = (sourceX * targetY) - (sourceY * targetX);
  float crossMag = sqrtf((crossX * crossX) + (crossY * crossY) + (crossZ * crossZ));
  float dot = (sourceX * targetX) + (sourceY * targetY) + (sourceZ * targetZ);

  if (crossMag > 1e-6f) {
    float axisX = crossX / crossMag; float axisY = crossY / crossMag; float axisZ = crossZ / crossMag;
    float angle = acosf(constrain(dot, -1.0f, 1.0f));
    float c = cosf(angle); float s = sinf(angle); float oneMinusC = 1.0f - c;

    imuToRobot[0][0] = c + (axisX * axisX * oneMinusC);
    imuToRobot[0][1] = (axisX * axisY * oneMinusC) - (axisZ * s);
    imuToRobot[0][2] = (axisX * axisZ * oneMinusC) + (axisY * s);
    imuToRobot[1][0] = (axisY * axisX * oneMinusC) + (axisZ * s);
    imuToRobot[1][1] = c + (axisY * axisY * oneMinusC);
    imuToRobot[1][2] = (axisY * axisZ * oneMinusC) - (axisX * s);
    imuToRobot[2][0] = (axisZ * axisX * oneMinusC) - (axisY * s);
    imuToRobot[2][1] = (axisZ * axisY * oneMinusC) + (axisX * s);
    imuToRobot[2][2] = c + (axisZ * axisZ * oneMinusC);
  } else if (dot < 0.0f) {
    imuToRobot[1][1] = -1.0f; imuToRobot[2][2] = -1.0f;
  }
}

void rotateIntoRobotFrame(float inputX, float inputY, float inputZ, float& outputX, float& outputY, float& outputZ) {
  outputX = (imuToRobot[0][0] * inputX) + (imuToRobot[0][1] * inputY) + (imuToRobot[0][2] * inputZ);
  outputY = (imuToRobot[1][0] * inputX) + (imuToRobot[1][1] * inputY) + (imuToRobot[1][2] * inputZ);
  outputZ = (imuToRobot[2][0] * inputX) + (imuToRobot[2][1] * inputY) + (imuToRobot[2][2] * inputZ);
}

void setLED(){
  digitalWrite(led1Pin, line_sensors[0] == LOW); 
  digitalWrite(led2Pin, line_sensors[1] == LOW);
}

void writeMotors() {
  const int leftSpeed = motorsEnabled ? motors[0] : 0;
  const int rightSpeed = motorsEnabled ? motors[1] : 0;
  // 'static' means it remembers these values between loops
  static int lastLeftSpeed = -999;
  static int lastRightSpeed = -999;

  // If the speed hasn't changed, do nothing! Let the hardware PWM keep running smoothly.
  if (leftSpeed == lastLeftSpeed && rightSpeed == lastRightSpeed) {
      return; 
  }

  // Save the new speeds
  lastLeftSpeed = leftSpeed;
  lastRightSpeed = rightSpeed;

  auto setMotor = [](int pinF, int pinB, int speed) {
    if (speed > 0) { 
        analogWrite(pinF, speed); 
        analogWrite(pinB, 0); 
    } 
    else if (speed < 0) { 
        analogWrite(pinB, -speed); 
        analogWrite(pinF, 0); 
    } 
    else { 
        analogWrite(pinF, 0); 
        analogWrite(pinB, 0); 
    }
  };
  
  setMotor(leftF, leftB, leftSpeed);
  setMotor(rightF, rightB, rightSpeed);
}

void writeServo(int pin, double deg) {
  if (deg < 0) deg = 0;
  if (deg > 180) deg = 180;
  long pulse_width_us = map(deg, 0, 180, 1000, 2000);
  robotServo.writeMicroseconds(pulse_width_us);
}

// RESTORED: Debug Implementation Functions
void debug() {
  printCounter++;
  if (printCounter % 250 == 0) {
    debugAverages();
    debugDIP();
    debugFusedValues();
    aliFuncln("");
    debugLine();
  }
}

void debugLine(){
  for(int i = 0; i < 2; i++){
    aliFunc(line_sensors[i]);
    aliFunc(" ");
  }
  aliFuncln(""); 
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
  float* avgs = ws.get_sensors_avg();
  for(int i = 0; i < 5; i++){
    aliFunc(avgs[i]);
    aliFunc(" ");
  }
}

void debugFusedValues() {
    if (dips[2] == LOW) {
        Serial.print("Roll/Pitch: "); 
        Serial.print(rollDeg); Serial.print(" "); 
        Serial.println(pitchDeg); 
        
        Serial.print("Linear Accel XYZ: "); 
        Serial.print(linearAccelX); Serial.print(" "); 
        Serial.print(linearAccelY); Serial.print(" "); 
        Serial.println(linearAccelZ);
    }
}

void debugEnemy(EnemyPosition ep){
  switch(ep) {
    case NONE:        aliFunc("NONE"); break;
    case LEFT:        aliFunc("LEFT"); break;
    case FRONT:       aliFunc("FRONT"); break;
    case RIGHT:       aliFunc("RIGHT"); break;
    case MIDLEFT:     aliFunc("MIDLEFT"); break;
    case MIDRIGHT:    aliFunc("MIDRIGHT"); break;
    case FARFRONT:    aliFunc("FARFRONT"); break;
    case FLAG_LEFT:   aliFunc("FLAG_LEFT"); break;
    case FLAG_RIGHT:  aliFunc("FLAG_RIGHT"); break;
    case FRONT_LEFT:  aliFunc("FRONT_LEFT"); break;   
    case FRONT_RIGHT: aliFunc("FRONT_RIGHT"); break;  
  }
  aliFuncln("");
}
