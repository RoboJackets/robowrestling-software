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
int FR = D7;		// A5 does not support attachInterrupt, so jump A5 to D7 on the board, also cut INT line
int BL = D5;
int BR = D6;

int RS = D4;

int Lmotor = D2;
int Rmotor = D3;

char past;          //what direction the robot was moving previously
int cur;            // current timer
int prevFlag;       // timer since last movement
int lineFlag;       // flag to mark if line has been met
boolean pivotFlag;  // flag to mark if the robot has pivoted
boolean moving;

// max and minimum motor speeds
int maxS = 150;
int minS = 110;
int maxR = 150;
int minR = 110;

int state;          // movement state of robot

// thresholds for movement timers
int degreesMin = 300; // turn a little
int degrees90 = 900; // turn 90 degrees
int degrees180 = 900; // turn 180 degrees
int startSpinR = 273; // time spinning right at start
int startTurnL = 600; // time turning left at start
int startSpinL = 300; // time spinning left at start
int startCross = 100; // time crossing the arena
int pivotBack = 500; // time moving back at pivot
int pivotSpinR = 700; // time spinning right at pivot
int pivotTurnL = 2000; // time turning left at pivot
int pivotSpinL = 700; // time spinning left at pivot

// flags set for line sensors
boolean FLflag = false;
boolean FRflag = false;
boolean BLflag = false;
boolean BRflag = false;

// remote start flag
boolean RSflag = false;

SYSTEM_THREAD(ENABLED);
SYSTEM_MODE(MANUAL);	// fully offline

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


void runDiagnostic() {
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

  LESC.writeMicroseconds(1600);
  RESC.writeMicroseconds(1600);
}

void move(int motor, int speed, int direction){
  // usage: x_ESC.writeMicroseconds(pwm)
  // pwm should between 1100 and 1800
  // 1100 for maximum reverse, 1800 for maximum forward
  // 30% throttle is 1500 +/- 300*0.3 = 1500 +/- 90

  int pwm = 1500;       // default is ESC stopped

  if(direction == 1) {  // forward
    pwm = 1500 + speed;
  } else {              // reverse
    pwm = 1500 - speed;
  }
  if(motor == 1) {      // RIGHT ESC
    RESC.writeMicroseconds(pwm);
  } else {              // LEFT ESC
    LESC.writeMicroseconds(pwm);
  }
}

void stop(){
  RESC.writeMicroseconds(1500);
  LESC.writeMicroseconds(1500);
}

void movement(int state) {
  switch (state) {
    case 0: //forward
      //move(2, 100, 0);
      move(1, maxR, 1);
      move(2, maxS, 0);
      moving = true;
      break;
    case 1: //attack
      move(1, 200, 1);
      move(2, 200, 0);
      moving = true;
      break;
    case 2: //left
      move(1, maxR, 1);
      move(2, minS, 0);
      moving = true;
      break;
    case 3: //right
      move(1, minR, 1);
      move(2, maxS, 0);
      moving = true;
      break;
    case 4: //left in place
      move(1, maxR, 1);
      move(2, maxS, 1);
      moving = true;
      break;
    case 5: //right in place
      move(1, maxR, 0);
      move(2, maxS, 0);
      moving = true;
      break;
    case 6: //back right and left
      if (cur - prevFlag < degreesMin) {
        move(1, minR, 0);
        move(2, maxS, 1);
      } else if (cur - prevFlag < degrees90) {
        move(1, maxR, 1);
        move(2, maxS, 1);
      } else {
        lineFlag = 0;
      }
      moving = true;
      break;
    case 7: //back right and right
      if (cur - prevFlag < degreesMin) {
        move(1, minR, 0);
        move(2, maxS, 1);
      } else if (cur - prevFlag < degrees90) {
        move(1, maxR, 0);
        move(2, maxS, 0);
      } else {
        lineFlag = 0;
      }
      moving = true;
      break;
    case 8: //back left and right
      if (cur - prevFlag < degreesMin) {
        move(1, maxR, 0);
        move(2, minS, 1);
      } else if (cur - prevFlag < degrees90) {
        move(1, maxR, 0);
        move(2, maxS, 0);
      } else {
        lineFlag = 0;
      }
      moving = true;
      break;
    case 9: //back left and left
      if (cur - prevFlag < degreesMin) {
        move(1, maxR, 0);
        move(2, minS, 1);
      } else if (cur - prevFlag < degrees90) {
        move(1, maxR, 1);
        move(2, maxS, 1);
      } else {
        lineFlag = 0;
      }
      moving = true;
      break;
    case 10: //back and spin 180
      if (cur - prevFlag < degreesMin) {
        move(1, maxR, 0);
        move(2, maxS, 0);
      } else if (cur - prevFlag < degrees180) {
        move(1, maxR, 0);
        move(2, maxS, 0);
      } else {
        lineFlag = 0;
      }
      moving = true;
      break;
    case 11: //startup movement: spin right, turn left, spin left, go forward
      if (cur - prevFlag < startSpinR) {
        move(1, maxR, 0);
        move(2, maxS, 0);
      } else if (cur - prevFlag < startTurnL + startSpinR) {
        move(1, maxR, 1);
        move(2, minS, 0);
      } else if (cur - prevFlag < startSpinL + startTurnL + startSpinR) {
        move(1, maxR, 1);
        move(2, maxS, 1);
      } else {
        past = 'f';
        pivotFlag = false;
      }
      moving = true;
      break;
    case 12: //pivot: go back, spin right, turn left, spin left, go forward
      if (cur - prevFlag < pivotBack) {
        move(1, maxR, 0);
        move(2, maxS, 0);
      } else if (cur - prevFlag < pivotSpinR + pivotBack) {
        move(1, maxR, 0);
        move(2, maxS, 0);
      } else if (cur - prevFlag < pivotTurnL + pivotSpinR + pivotBack) {
        move(1, maxR, 1);
        move(2, minS, 0);
      } else if (cur - prevFlag < pivotSpinL + pivotTurnL + pivotSpinR + pivotBack) {
        move(1, maxR, 1);
        move(2, maxS, 1);
      } else {
        past = 'f';
        pivotFlag = false;
      }
      moving = true;
      break;
  }
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

  attachInterrupt(FL,FLISR,FALLING);
  attachInterrupt(FR,FRISR,FALLING);
  attachInterrupt(BL,BLISR,FALLING);
  attachInterrupt(BR,BRISR,FALLING);

  attachInterrupt(RS,RSISR,CHANGE);

  LESC.attach(Lmotor);
  LESC.writeMicroseconds(1500);
  RESC.attach(Rmotor);
  RESC.writeMicroseconds(1500);

  moving = true;

  //state = 11;
}

void loop()
{
  if (!FLflag || !FRflag || !BRflag || !BLflag) {
    moving = false;
    stop();
  } else {
    movement(0);
  }

  cur = millis();
  prevFlag = cur;

  runDiagnostic();
  stop();
}
