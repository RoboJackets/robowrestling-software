// This #include statement was automatically added by the Particle IDE.

#include "Particle.h"

#include <VL53L0X.h>
#include <LIS3DH.h>

#include <thresholds.h>

#if !defined(PARTICLE)
#  include <Wire.h>
#endif

// Time of Flight sensors
VL53L0X sensor0;
VL53L0X sensor1;
VL53L0X sensor2;
VL53L0X sensor3;
int LL_distance;
int LM_distance;
int RM_distance;
int RR_distance;

// Line sensors
int FL = D7;    // AUX BOARD SWITCHED FL and FR up
int FR = A4;    // A5 does not support attachInterrupt, so jump A5 to D7 on the board, also cut INT line
int BL = D5;
int BR = D6;
boolean FLflag = true;  // active low
boolean FRflag = true;
boolean BLflag = true;
boolean BRflag = true;

// Remote switch module
int RS = D4;
boolean RSflag = false;

// Car ESCs
Servo LESC;
Servo RESC;
int Lmotor = D2;
int Rmotor = D3;
int L_command = 1500;
int R_command = 1500;

// Photon settings
SYSTEM_THREAD(ENABLED);
SYSTEM_MODE(MANUAL);    // fully offline

// Accelerometer
const unsigned long PRINT_SAMPLE_PERIOD = 100;
int curAccel = 0;
void getAccel();        // ISR prototype
LIS3DHSample sample;
LIS3DHI2C accel(Wire, 0, WKP);

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
  Serial.begin(9600); // *** need to modify before comp ***
} 

void interrupt_init() {
  // Line sensors
  attachInterrupt(FL, FLISR, CHANGE);
  attachInterrupt(FR, FRISR, CHANGE);
  attachInterrupt(BL, BLISR, CHANGE);
  attachInterrupt(BR, BRISR, CHANGE);
  // Remote switch
  attachInterrupt(RS, RSISR, CHANGE);
  // Accel software timer
  Timer accelTimer(PRINT_SAMPLE_PERIOD, getAccel); 
  accelTimer.start();  
}

void ESC_init() {
  // Necessary for Servo objects
    LESC.attach(Lmotor);
    RESC.attach(Rmotor);
    // Write stop command
    LESC.writeMicroseconds(1500);
    RESC.writeMicroseconds(1500);
}

void robot_init() {
  while(!RSflag) {    // initial LOW
    Serial.println("Waiting for Start");
  }
  Serial.println("Starting in 5 seconds...");
  delay(5000);
  Serial.println("GO!");    
}

void getAccel() {
  accel.getSample(sample);
  curAccel = sample.x;
}

void setup() {
  tof_init();         // ToF and I2C
  accel_init();       // accelerometer
  others_init();      // line, remote, esc, ***printing***
  interrupt_init();   // interrupts for lines and remote
  ESC_init();         // Car ESCs

  robot_init();       // 5-second countdown after remote switch is activated
}

void stop() {
    LESC.writeMicroseconds(1500);
    RESC.writeMicroseconds(1500);    
}

void loop() {
    // Handle remote switching
    if(RSflag == LOW) {
        stop();
        while(true);    // must power-cycle to restart operation
    }

    // Read from Time of Flight sensors
    LL_distance = sensor0.readRangeContinuousMillimeters();
    LM_distance = sensor1.readRangeContinuousMillimeters();
    RM_distance = sensor2.readRangeContinuousMillimeters();
    RR_distance = sensor3.readRangeContinuousMillimeters();
    // if (sensor0.timeoutOccurred() || sensor1.timeoutOccurred() || sensor2.timeoutOccurred() || sensor3.timeoutOccurred()) { Serial.print(" SENSOR TIMEOUT"); }

    /* Need to handle
        Line- states
            FLflag, FRflag, BLflag, BRflag
        accel 
            curAccel
        ESCs
            L_command, R_command
    */

    /* 
    // States in order of importance

    // LINE STATES

    // STALL STATE
    if(curAccel > SOME_THRESHOLD) { // and also if moving, last command?
        stop();
        backup();
        // some flag that will skip the search/attack
    } 

    // SEARCH STATE

    // ATTACK STATE


    */


    /*
    States
        Start-up
            requires turns
        Normal:
            Search - ?
            Attack - Handled by Fuzzy
        Incidental:
            Line - 4
            Stall - 1, curAccel
    Output: always a L_command and R_command
    */

     
}