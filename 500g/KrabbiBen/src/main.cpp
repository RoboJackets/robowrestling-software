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
bool rightLineSensorEnabled = false; // Right line sensor is broken; reads as "no border" while false.
const unsigned long startupDelayMs = 0;
const int START_MODULE_ACTIVE_STATE = HIGH;
long currentMillis = 0;
bool startupDelayComplete = false;
bool startSignalReceived = false;
bool imuCalibrationDone = false;
unsigned long loopCounter = 0;
unsigned long lastImuReadMicros = 0;

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
bool imuImpactLatched = false;
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
void pullLineSensors();
void updateIMU();
void updateOrientation();
void writeMotors();
void stopDrive();
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

// Build each telemetry snapshot in RAM so USB backpressure cannot block driving.
class DebugFrame : public Print {
public:
  uint8_t data[512];
  size_t length = 0;
  size_t write(uint8_t value) override {
    if (length == sizeof(data)) return 0;
    data[length++] = value;
    return 1;
  }
};
Print* telemetryOutput = &Serial;

// Debug mode (serial telemetry + test mode) only when DIP 3 is on and DIPs 1 and 2 are off.
bool debugMode() {
  return dips[0] == HIGH && dips[1] == HIGH && dips[2] == LOW;
}

template <typename T>
void aliFunc(const T& value) {
  if (debugMode()) telemetryOutput->print(value);
}
template <typename T>
void aliFuncln(const T& value) {
  if (debugMode()) telemetryOutput->println(value);
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
  Serial.begin(115200);
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
  dips[0] = digitalRead(dip1);
  dips[1] = digitalRead(dip2);
  dips[2] = digitalRead(dip3);
  pinMode(led1Pin, OUTPUT);
  pinMode(led2Pin, OUTPUT);

  Wire.setSCL(imuSCL);
  Wire.setSDA(imuSDA);
  Wire.begin();

  bool imuAvailable = mpu.begin();

  // Initialize Servo
  robotServo.writeMicroseconds(1000); 
  robotServo.attach(servoPin);
  writeServo(servoPin, 0); 

  if (imuAvailable) {
    mpu.setAccelerometerRange(MPU6050_RANGE_8_G);
    mpu.setGyroRange(MPU6050_RANGE_500_DEG);
    mpu.setFilterBandwidth(MPU6050_BAND_21_HZ);
    calibrateImuMounting();
    imuCalibrationDone = true;
    filter.begin(400.0f);
    lastGyroMicros = micros();
  } else {
    aliFuncln("IMU not detected; driving disabled.");
  }
  // aliFuncln("Started");
}

void loop() {
  ++loopCounter;
  pullSensors(); 
  currentMillis = millis();
  ws.get_sensors_avg();

  bool testMode = debugMode();
  bool startModuleActive = (digitalRead(startPin) == START_MODULE_ACTIVE_STATE);
  // Stop motor PWM before any peripheral operation can delay this loop.
  if (!startModuleActive || !imuCalibrationDone) stopDrive();
  // Apply edge escape motor output before I2C polling or serial telemetry.
  if (startModuleActive && imuCalibrationDone && startupDelayComplete &&
      algo.respondToLine(ws.line_check())) {
    impactOccurred = false;
    writeMotors();
    setLED();
  }

  // Keep IMU telemetry live even when the start module is inactive.
  bool imuSampleUpdated = false;
  if (imuCalibrationDone && micros() - lastImuMicros >= IMU_INTERVAL_MICROS) {
    lastImuMicros = micros();
    unsigned long readStartMicros = micros();
    updateIMU();
    lastImuReadMicros = micros() - readStartMicros;
    updateOrientation();
    imuSampleUpdated = true;
  }


  // The start signal may have changed while the blocking IMU read ran.
  startModuleActive = (digitalRead(startPin) == START_MODULE_ACTIVE_STATE);
  // Driving requires an active start module and a working, calibrated IMU.
  if (startModuleActive && imuCalibrationDone) {
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
        debug();
        return;
      }
      startupDelayComplete = true;
    }
    
    // Advance the collision filter only when a fresh IMU sample arrives.
    bool impactJustHappened = false;
    if (imuSampleUpdated) {
      bool impactDetected = detectImuImpact();
      impactJustHappened = impactDetected && !imuImpactLatched;
      imuImpactLatched = impactDetected;
    }

    setLED();

    EnemyPosition enemyPos = ws.enemy_pos();
    LinePosition linePos = ws.line_check();
    
    // Collision Trigger Logic
    bool enemyInPushingArc = (enemyPos == FRONT || enemyPos == FRONT_LEFT || enemyPos == FRONT_RIGHT || enemyPos == MIDLEFT || enemyPos == MIDRIGHT || enemyPos == FARFRONT);
    bool imuImpactArmed = (linePos == OFF_LINE) && enemyInPushingArc;

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
    // Catch a border reached during the blocking IMU transaction too.
    pullLineSensors();
    currentMillis = millis();
    algo.selectMode(linearAccelX, dips[0], dips[1], 0.0f);
    
    // DIP 3 on: keep the flags up for the whole match.
    bool flagsStayUp = (dips[2] == LOW);
    writeServo(servoPin, flagsStayUp ? 0 : 250); 
    writeMotors();
    
    // RESTORED: Fire debug prints
    debug();
  } else {
    stopDrive();
    debug();
    return;
  }
}

void pullSensors() {
  ir_sensors[0] = digitalRead(leftSideSensor);
  ir_sensors[1] = digitalRead(leftSensor);
  ir_sensors[2] = digitalRead(middleSensor);
  ir_sensors[3] = digitalRead(rightSensor);
  ir_sensors[4] = digitalRead(rightSideSensor);
  
  pullLineSensors();
  
  dips[0] = digitalRead(dip1);
  dips[1] = digitalRead(dip2);
  dips[2] = digitalRead(dip3);
}

void pullLineSensors() {
  // Digital, active-LOW line outputs; input pull-ups are configured in setup().
  line_sensors[0] = digitalRead(leftLineSensor);
  line_sensors[1] = rightLineSensorEnabled ? digitalRead(rightLineSensor) : HIGH;
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
  // Recheck at the actual output write, not just at the beginning of loop().
  const bool driveAllowed = motorsEnabled && imuCalibrationDone &&
    digitalRead(startPin) == START_MODULE_ACTIVE_STATE;
  const int leftSpeed = driveAllowed ? motors[0] : 0;
  const int rightSpeed = driveAllowed ? motors[1] : 0;
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
        // Clear the opposite direction before enabling PWM in this direction.
        analogWrite(pinB, 0); 
        analogWrite(pinF, speed);
    } 
    else if (speed < 0) { 
        analogWrite(pinF, 0); 
        analogWrite(pinB, -speed);
    } 
    else { 
        analogWrite(pinF, 0); 
        analogWrite(pinB, 0); 
    }
  };
  
  setMotor(leftF, leftB, leftSpeed);
  setMotor(rightF, rightB, rightSpeed);
}

void stopDrive() {
  startSignalReceived = false;
  startupDelayComplete = false;
  startup_delay_timer.reset();
  impactOccurred = false;
  imuImpactLatched = false;
  kalmanForwardAccelEstimate = 0.0f;
  kalmanForwardAccelCovariance = 1.0f;
  lastAccelMagnitude = 0.0f;
  algo.resetState();
  writeMotors();
  writeServo(servoPin, 0);
  digitalWrite(led1Pin, LOW);
  digitalWrite(led2Pin, LOW);
}

void writeServo(int pin, double deg) {
  if (deg < 0) deg = 0;
  if (deg > 180) deg = 180;
  long pulse_width_us = map(deg, 0, 180, 1000, 2000);
  robotServo.writeMicroseconds(pulse_width_us);
}

// Debug mode enables 10 Hz telemetry even when the start module is inactive.
void debug() {
  static DebugFrame frame;
  static size_t sent = 0;
  if (!debugMode() || !Serial.dtr()) {
    frame.length = sent = 0;
    return;
  }
  static unsigned long lastDebugMillis = 0;
  unsigned long nowMs = millis();
  if (sent == frame.length && nowMs - lastDebugMillis >= 100) {
    frame.length = sent = 0;
    lastDebugMillis = nowMs;
    telemetryOutput = &frame;

    aliFunc("Loop: "); aliFunc(loopCounter);
    aliFunc("  t_ms: "); aliFunc(nowMs);
    aliFunc("  IMU read_us: "); aliFuncln(lastImuReadMicros);
    aliFunc("START: "); aliFunc(digitalRead(startPin));
    aliFunc("  DIP 1/2/3: "); debugDIP();
    aliFunc("IR raw [left-side left center right right-side]: ");
    debugIR(); aliFuncln("");
    aliFunc("IR averages: "); debugAverages(); aliFuncln("");
    aliFunc("Line digital [left right], 0=border: "); debugLine();
    aliFunc("Motor command [left right]: ");
    aliFunc(motorsEnabled ? motors[0] : 0); aliFunc(" ");
    aliFuncln(motorsEnabled ? motors[1] : 0);
    aliFunc("Full charge: "); aliFunc(algo.isFullChargeMode());
    aliFunc("  Filtered forward accel: "); aliFuncln(lastAccelMagnitude);
    if (imuCalibrationDone) {
      debugFusedValues();
    } else {
      aliFuncln("IMU unavailable; driving disabled");
    }
    aliFuncln("");
    telemetryOutput = &Serial;
  }

  int available = Serial.availableForWrite();
  if (available <= 0) return;
  size_t remaining = frame.length - sent;
  size_t count = remaining < (size_t)available ? remaining : (size_t)available;
  if (count > 0) sent += Serial.write(frame.data + sent, count);
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
  aliFunc(dips[0]);
  aliFunc(" ");
  aliFunc(dips[1]);
  aliFunc(" ");
  aliFuncln(dips[2]);
}

void debugAverages() {
  const float* avgs = ws.sensors_avg();
  for(int i = 0; i < 5; i++){
    aliFunc(avgs[i]);
    aliFunc(" ");
  }
}

void debugFusedValues() {
  aliFunc("Roll/Pitch: ");
  aliFunc(rollDeg); aliFunc(" ");
  aliFuncln(pitchDeg);

  aliFunc("Linear Accel XYZ: ");
  aliFunc(linearAccelX); aliFunc(" ");
  aliFunc(linearAccelY); aliFunc(" ");
  aliFuncln(linearAccelZ);
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
