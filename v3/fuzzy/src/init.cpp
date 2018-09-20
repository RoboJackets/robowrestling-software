//
// Created by Logan Schick on 9/6/2018.
//

#include <Particle.h>

#include <VL53L0X.h>

#if !defined(PARTICLE)
#  include <Wire.h>
#endif

#include <sensors.h>

#include <movement.h>

#include <init.h>

//Defining variables
int FL = D7;    // AUX BOARD SWITCHED FL and FR up
int FR = A4;    // A5 does not support attachInterrupt, so jump A5 to D7 on the board, also cut INT line
int BL = D5;
int BR = D6;
boolean FLflag = true;
boolean FRflag = true;
boolean BLflag = true;
boolean BRflag = true;
int cur = 0;
int prevFlag = 0;
boolean prevFlagSet = false;
boolean start = true;
int RS = D4;
boolean RSflag = false;
int Lmotor = D2;
int Rmotor = D3;

// Particle Photon settings
SYSTEM_THREAD(ENABLED);
SYSTEM_MODE(MANUAL);

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

void others_init() {
    // Line sensors
    pinMode(FL, INPUT);
    pinMode(FR, INPUT);
    pinMode(BL, INPUT);
    pinMode(BR, INPUT);
    // Remote switch
    pinMode(RS, INPUT);
    // Car ESCs
    pinMode(Lmotor, OUTPUT);
    pinMode(Rmotor, OUTPUT);

    // ***Remove for competition***
    // ***Serial monitor***
    // Serial.begin(9600);	// *** need to modify before comp ***
}

void interrupt_init() {
    // Line sensors
    attachInterrupt(FL, FLISR, CHANGE);
    attachInterrupt(FR, FRISR, CHANGE);
    attachInterrupt(BL, BLISR, CHANGE);
    attachInterrupt(BR, BRISR, CHANGE);
    // Remote switch
    attachInterrupt(RS, RSISR, CHANGE);

    // NOT USED
    // Accel software timer
    // Timer accelTimer(PRINT_SAMPLE_PERIOD, getAccel);
    // accelTimer.start();
}

void ESC_init() {
    // Necessary for Servo objects
    LESC.attach(Lmotor);
    RESC.attach(Rmotor);
    // Write stop command
    LESC.writeMicroseconds(1500);
    RESC.writeMicroseconds(1500);
}

void line_init() {
    // moving = true;
    prevFlag = millis();
}

void robot_init() {
    while(RSflag == LOW) {    // initial LOW
        Serial.println("Waiting for Start");
    }
    Serial.println("Starting in 5 seconds...");
    delay(5000);
    // Serial.println("GO!");
}

void startUp() {
    if (!prevFlagSet) {
        prevFlag = cur;
        prevFlagSet = true;
    } else {
        movement(2);
    }
}
