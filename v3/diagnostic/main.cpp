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

Servo LESC;
Servo RESC;

int FL = A4;
int FR = D7;		// A5 does not support attachInterrupt, so jump A5 to D7 on the board
int BL = D5;
int BR = D6;

int RS = D4;

int Lmotor = D2;
int Rmotor = D3;

boolean FLflag = false;
boolean FRflag = false;
boolean BLflag = false;
boolean BRflag = false;

boolean RSflag = false;

// Accel
SYSTEM_THREAD(ENABLED);
SYSTEM_MODE(MANUAL);
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

void setup()
{
  pinMode(A0, OUTPUT);
  pinMode(A1, OUTPUT);
  pinMode(A2, OUTPUT);
  pinMode(A3, OUTPUT);
  
  pinMode(FL, INPUT);
  pinMode(FR, INPUT);
  pinMode(BL, INPUT);
  pinMode(BR, INPUT);
  
  pinMode(RS, INPUT);
  
  pinMode(Lmotor, OUTPUT);
  pinMode(Rmotor, OUTPUT);
  
  Serial.begin(9600);
  
  //reset all pins
  digitalWrite(A0, LOW);
  digitalWrite(A1, LOW);
  digitalWrite(A2, LOW);
  digitalWrite(A3, LOW);
  delay(500);
  
  // need to initialize i2c
  // protocol AFTER driving shdn pins low
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
  
  attachInterrupt(FL,FLISR,FALLING);
  attachInterrupt(FR,FRISR,FALLING);
  attachInterrupt(BL,BLISR,FALLING);
  attachInterrupt(BR,BRISR,FALLING);
  
  attachInterrupt(RS,RSISR,CHANGE);
  
  Wire.setSpeed(CLOCK_SPEED_100KHZ);  // need to initialize i2c protocol after driving shdn pins low
  Wire.begin();
  
  LESC.attach(Lmotor);
  LESC.writeMicroseconds(1500);
  RESC.attach(Rmotor);
  RESC.writeMicroseconds(1500);

  // Start continuous back-to-back mode (take readings as
  // fast as possible).  To use continuous timed mode
  // instead, provide a desired inter-measurement period in
  // ms (e.g. sensor.startContinuous(100)).
  sensor0.startContinuous(10);
  sensor1.startContinuous(10);
  sensor2.startContinuous(10);
  sensor3.startContinuous(10);
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
  // if (FLflag) {
  //     Serial.print(FLflag);
  //     FLflag = false;
  // } else {
      Serial.print(FLflag);
  // }
  Serial.print(" | ");
  Serial.print("front right:");
  // if (FRflag) {
  //     Serial.print(FRflag);
  //     FRflag = false;
  // } else {
      Serial.print(FRflag);
  // }
  Serial.print(" | ");
  Serial.print("back left:");
  // if (BLflag) {
  //     Serial.print(BLflag);
  //     BLflag = false;
  // } else {
      Serial.print(BLflag);
  // }
  Serial.print(" | ");
  Serial.print("back right:");
  // if (BRflag) {
  //     Serial.print(BRflag);
  //     BRflag = false;
  // } else {
      Serial.print(BRflag);
  // }
  
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
  
  LESC.writeMicroseconds(1600);
  RESC.writeMicroseconds(1600);
}
