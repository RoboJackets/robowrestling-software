// This #include statement was automatically added by the Particle IDE.

#include <Particle.h>

#include <LIS3DH.h>

#if !defined(PARTICLE)
#  include <Wire.h>
#endif

/* This firmware produces a runtime error
#include <Adafruit_LIS3DH.h>

#include "Particle.h"
//#include <stdio.h>
#include "Wire.h"

void toggleState(void);
int state = 0;

int intPin = D7;

int analogvalue;

void setup()
{
    Serial.begin(9600);
    Adafruit_LIS3DH lis = Adafruit_LIS3DH();
    lis.setClick(1, 77);
    Wire.begin();
    pinMode(intPin, INPUT);
    //attachInterrupt(intPin, toggleState, RISING);
}

void loop()
{
    delay(10);
    Serial.println(state);
}

void toggleState()
{
    state = !state;
}

*/

void getAccel();
int accelPin = D1;
int curAccel = 0;

LIS3DHSample sample;

Timer timer(100, getAccel);
const unsigned long PRINT_SAMPLE_PERIOD = 100;
LIS3DHI2C accel(Wire, 0, WKP);
unsigned long lastPrintSample = 0;

void getAccel() {
  accel.getSample(sample);
  curAccel = sample.x;
}


//int state;          // movement state of robot


// Accelerometer

void accel_init() {
	LIS3DHConfig config;
	config.setAccelMode(LIS3DH::RATE_100_HZ);

	bool setupSuccess = accel.setup(config);
	Serial.printlnf("setupSuccess=%d", setupSuccess);
}


// void runDiagnostic() {
//   if (millis() - lastPrintSample >= PRINT_SAMPLE_PERIOD) {
// 		lastPrintSample = millis();
//     Serial.print("Accel values: ");
// 		if (accel.getSample(sample)) {
// 			Serial.printlnf("%d,%d,%d", sample.x, sample.y, sample.z);
// 		}
// 		else {
// 			Serial.println("no sample");
// 		}
// 	}
// }

void setup()
{
  pinMode(accelPin, INPUT);
  Serial.begin(9600);

  accel_init();
  timer.start();
  delay(1000);
}

void loop()
{
  //runDiagnostic();
	Serial.println(curAccel);
}
