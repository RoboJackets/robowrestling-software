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

// Line sensors: Front Left, Front Right, Back Left, Back Right
int FL = A2;    // AUX BOARD SWITCHED FL and FR up
int FR = A3;    // A5 does not support attachInterrupt, so jump A5 to D7 on the board, also cut INT line
int BL = A4;
int BR = A6;
// Line sensor flags that are flipped at an interrupt
boolean FLflag = true;
boolean FRflag = true;
boolean BLflag = true;
boolean BRflag = true;

// timer for current time in milis()
int cur = 0;

// timer for time elapsed after cur for timed movements
int prevFlag = 0;

// flag that helps prioritize timed movements, which are most likely for line detection
boolean prevFlagSet = false;

// flag to denote whether or not we want to run startup sequence
boolean start = true;

// remote start pin
int RS = D4;
// remote start flag that is flipped once we press the button on the remote
boolean RSflag = false;

// setting pins for the motors
int Lmotor = D2;
int Rmotor = D3;

//Setting flags to line sensors pins during an interrupt handler
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

// interrupt handler for remote start
void RSISR() {
    RSflag = digitalRead(RS);
}

//Setting up TOF sensors
//Add 2 more ToF sensors All the pins need to be fixed bc they've changed
void tof_init() {
    pinMode(A0, OUTPUT);
    pinMode(A1, OUTPUT);
    pinMode(A2, OUTPUT);
    pinMode(A3, OUTPUT);

    //If same setup for new ToF
    //pinMode(A4, OUTPUT)
    //pinMode(A5, OUTPUT)
    digitalWrite(A0, LOW);
    digitalWrite(A1, LOW);
    digitalWrite(A2, LOW);
    digitalWrite(A3, LOW);
    //If same setup for new ToF
    //digitalWrite(A4, OUTPUT)
    //digitalWrite(A5, OUTPUT)
    delay(500);

    Wire.setSpeed(CLOCK_SPEED_100KHZ);  // need to initialize i2c protocol after driving shdn pins low
    Wire.begin();

    delay(10);
    digitalWrite(A0, HIGH);
    digitalWrite(A1, HIGH);
    digitalWrite(A2, HIGH);
    digitalWrite(A3, HIGH);
    //If same setup for new ToF
    //digitalWrite(A4, HIGH)
    //digitalWrite(A5, HIGH)
    delay(10);
    digitalWrite(A1, LOW);
    digitalWrite(A2, LOW);
    digitalWrite(A3, LOW);
    //If same setup for new ToF
    //digitalWrite(A4, LOW)
    //digitalWrite(A5, LOW)
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
    // If same setup for new ToF
    // digitalWrite(A4, HIGH);
    // sensor4.init();
    // sensor4.setAddress(0x34);
    // sensor4.setTimeout(1000);
    // delay(10);
    // digitalWrite(A5, HIGH);
    // sensor5.init();
    // sensor5.setAddress(0x35);
    // sensor5.setTimeout(1000);
    // delay(10);

    // Start continuous back-to-back mode (take readings as
    // fast as possible).  To use continuous timed mode
    // instead, provide a desired inter-measurement period in
    // ms (e.g. sensor.startContinuous(100)).
    sensor0.startContinuous(10);
    sensor1.startContinuous(10);
    sensor2.startContinuous(10);
    sensor3.startContinuous(10);
    // If same setup for new ToF
    // sensor4.startContinuous(10);
    // sensor5.startContinuous(10);
}

//Setting up pins for line sensor, remote start, and ESCs to right modes
// INITIALIZE THE ENCODERS HERE
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

//Setting up line sensor interrupts so they can be triggered
// ADD THE INTERRUPT FOR THE ENCODERS HERE
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

// initialize prevFlag to be in unison with cur
void line_init() {
    // moving = true;
    prevFlag = millis();
}

//Wait 5 seconds before moving as per the rules
void robot_init() {
    while(RSflag == LOW) {    // initial LOW
        Serial.println("Waiting for Start");
    }
    Serial.println("Starting in 5 seconds...");
    delay(5000);
    // Serial.println("GO!");
}

// setting the startup sequence
void startUp() {
    if (!prevFlagSet) {
        prevFlag = cur;
        prevFlagSet = true;
    } else {
        movement(2);
    }
}
