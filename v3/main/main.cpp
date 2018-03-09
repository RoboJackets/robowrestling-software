#include "Particle.h"
#include <VL53L0X.h>
#include <LIS3DH.h>

#if !defined(PARTICLE)
#  include <Wire.h>
#endif

// ToF
VL53L0X sensor0;
VL53L0X sensor1;
VL53L0X sensor2;
VL53L0X sensor3;

// Accel
SYSTEM_THREAD(ENABLED);
SYSTEM_MODE(MANUAL);
const unsigned long PRINT_SAMPLE_PERIOD = 100;
LIS3DHI2C accel(Wire, 0, WKP);
unsigned long lastPrintSample = 0;

void accel_init() {
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
    sensor0.startContinuous();
    sensor1.startContinuous();
    sensor2.startContinuous();
    sensor3.startContinuous();
}

void setup() {
    Serial.begin(9600);
    Serial.println("Starting");
    accel_init();
}

void loop() {
	if (millis() - lastPrintSample >= PRINT_SAMPLE_PERIOD) {
		lastPrintSample = millis();

        uint16_t s1;
        uint16_t s2;
        uint16_t s3;
        uint16_t s4;

		LIS3DHSample sample;
		if (accel.getSample(sample)) {
			Serial.printlnf("%d,%d,%d", sample.x, sample.y, sample.z);
		}
		else {
			Serial.println("no sample");
		}
	}
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

    if (sensor0.timeoutOccurred() || sensor1.timeoutOccurred() || sensor2.timeoutOccurred() || sensor3.timeoutOccurred()) { Serial.print(" TIMEOUT"); }
    Serial.println();
}
