// This #include statement was automatically added by the Particle IDE.

#include "Particle.h"

#include <VL53L0X.h>
#include <LIS3DH.h>

#if !defined(PARTICLE)
#  include <Wire.h>
#endif

VL53L0X sensor0;
VL53L0X sensor1;
VL53L0X sensor2;
VL53L0X sensor3;

int FL = D7;    // AUX BOARD SWITCHED FL and FR up
int FR = A4;    // A5 does not support attachInterrupt, so jump A5 to D7 on the board, also cut INT line
int BL = D5;
int BR = D6;

int RS = D4;

Servo LESC;
Servo RESC;
int Lmotor = D2;
int Rmotor = D3;

boolean FLflag = true; // active low
boolean FRflag = true;
boolean BLflag = true;
boolean BRflag = true;

boolean RSflag = false;

SYSTEM_THREAD(ENABLED);
SYSTEM_MODE(MANUAL);  // fully offline

// Accelerometer
const unsigned long PRINT_SAMPLE_PERIOD = 100;
LIS3DHI2C accel(Wire, 0, WKP);
unsigned long lastPrintSample = 0;

void FLISR() {
    FLflag = digitalRead(FL);
}

void FRISR() {
    FRflag = digitalRead(FR);
}

void BLISR() {
    BLflag = digitalRead(BL);
}

void BRISR() {
    BRflag = digitalRead(BR);
}

void RSISR() {
    RSflag = digitalRead(RS);
}

void tof_init() {
    pinMode(A0, OUTPUT);
    pinMode(A1, OUTPUT);
    pinMode(A2, OUTPUT);
    pinMode(A3, OUTPUT);
    digitalWrite(A0, LOW);
    digitalWrite(A1, LOW);
    digitalWrite(A2, LOW);
    digitalWrite(A3, LOW);
    delay(500);

    Wire.setSpeed(CLOCK_SPEED_100KHZ);  // need to initialize i2c protocol after driving shdn pins low
    Wire.begin();

    delay(10);
    digitalWrite(A0, HIGH);
    digitalWrite(A1, HIGH);
    digitalWrite(A2, HIGH);
    digitalWrite(A3, HIGH);
    delay(10);
    digitalWrite(A1, LOW);
    digitalWrite(A2, LOW);
    digitalWrite(A3, LOW);
    sensor0.init();
    sensor0.setAddress(0x30);
    sensor0.setTimeout(1000);
    delay(10);
    digitalWrite(A1, HIGH);
    sensor1.init();
    sensor1.setAddress(0x31);
    sensor1.setTimeout(1000);
    delay(10);
    digitalWrite(A2, HIGH);
    sensor2.init();
    sensor2.setAddress(0x32);
    sensor2.setTimeout(1000);
    delay(10);
    digitalWrite(A3, HIGH);
    sensor3.init();
    sensor3.setAddress(0x33);
    sensor3.setTimeout(1000);
    delay(10);

    // Start continuous back-to-back mode (take readings as
    // fast as possible).  To use continuous timed mode
    // instead, provide a desired inter-measurement period in
    // ms (e.g. sensor.startContinuous(100)).
    sensor0.startContinuous(10);
    sensor1.startContinuous(10);
    sensor2.startContinuous(10);
    sensor3.startContinuous(10);
}

void accel_init() {
  LIS3DHConfig config;
  config.setAccelMode(LIS3DH::RATE_100_HZ);

  bool setupSuccess = accel.setup(config);
  Serial.printlnf("setupSuccess=%d", setupSuccess);
}

void setup()
{
  pinMode(FL, INPUT);
  pinMode(FR, INPUT);
  pinMode(BL, INPUT);
  pinMode(BR, INPUT);

  pinMode(RS, INPUT);

  pinMode(Lmotor, OUTPUT);
  pinMode(Rmotor, OUTPUT);

  Serial.begin(9600);

  tof_init();
  accel_init();

  attachInterrupt(FL,FLISR,CHANGE);
  attachInterrupt(FR,FRISR,CHANGE);
  attachInterrupt(BL,BLISR,CHANGE);
  attachInterrupt(BR,BRISR,CHANGE);

  attachInterrupt(RS,RSISR,CHANGE);

  LESC.attach(Lmotor);
  RESC.attach(Rmotor);
  LESC.writeMicroseconds(1500);
  RESC.writeMicroseconds(1500);

  while(!RSflag) {  // initial LOW
    Serial.println("Waiting for Start");
  }
  Serial.println("Starting in 5 seconds...");
  delay(5000);
  Serial.println("GO!");
}

void loop()
{
  Serial.print("remote status:");
  Serial.print(RSflag);
  Serial.print(" | ");

  Serial.print("sensor 0:");
  Serial.print(sensor0.readRangeContinuousMillimeters());
  Serial.print(" | ");
  Serial.print("sensor 1:");
  Serial.print(sensor1.readRangeContinuousMillimeters());
  Serial.print(" | ");
  Serial.print("sensor 2:");
  Serial.print(sensor2.readRangeContinuousMillimeters());
  Serial.print(" | ");
  Serial.print("sensor 3:");
  Serial.print(sensor3.readRangeContinuousMillimeters());
  if (sensor0.timeoutOccurred() || sensor1.timeoutOccurred() || sensor2.timeoutOccurred() || sensor3.timeoutOccurred()) { Serial.print(" SENSOR TIMEOUT"); }

  Serial.print(" | ");
  Serial.print("front left:");
  Serial.print(FLflag);

  Serial.print(" | ");
  Serial.print("front right:");
  Serial.print(FRflag);

  Serial.print(" | ");
  Serial.print("back left:");
  Serial.print(BLflag);

  Serial.print(" | ");
  Serial.print("back right:");
  Serial.print(BRflag);

  Serial.print(" | ");
  if (millis() - lastPrintSample >= PRINT_SAMPLE_PERIOD) {
    lastPrintSample = millis();

    LIS3DHSample sample;
    if (accel.getSample(sample)) {
      Serial.printlnf("%d,%d,%d", sample.x, sample.y, sample.z);
    }
    else {
      Serial.println("no sample");
    }
  }

  Serial.println();

  if(RSflag == LOW) {
    LESC.writeMicroseconds(1700);
    RESC.writeMicroseconds(1700);
  } else {
    LESC.writeMicroseconds(1500);
    RESC.writeMicroseconds(1500);
  }
  
}