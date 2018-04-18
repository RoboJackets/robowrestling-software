// A test of the eFLL fuzzy library
// Utilizes the VL53L0X sensor and Car ESCs

#include <Particle.h>

#include <FuzzyRule.h>
#include <FuzzyComposition.h>
#include <Fuzzy.h>
#include <FuzzyRuleConsequent.h>
#include <FuzzyOutput.h>
#include <FuzzyInput.h>
#include <FuzzyIO.h>
#include <FuzzySet.h>
#include <FuzzyRuleAntecedent.h>

#include <thresholds.h>

#include <VL53L0X.h>
#include <LIS3DH.h>

#if !defined(PARTICLE)
#  include <Wire.h>
#endif

// Time of Flight sensors
VL53L0X sensor0;	// RR
VL53L0X sensor1;	// RM
VL53L0X sensor2;	// LM
VL53L0X sensor3;	// LL
uint16_t LL_distance;
uint16_t LM_distance;
uint16_t RM_distance;
uint16_t RR_distance;

// Line sensors
int FL = D7;    // AUX BOARD SWITCHED FL and FR up
int FR = A4;    // A5 does not support attachInterrupt, so jump A5 to D7 on the board, also cut INT line
int BL = D5;
int BR = D6;
boolean FLflag = true; // active low
boolean FRflag = true;
boolean BLflag = true;
boolean BRflag = true;
int cur;
int prevFlag;
// boolean moving;
boolean prevFlagSet = false;

// Remote switch module
int RS = D4;
boolean RSflag = false;

// Accelerometer
const unsigned long PRINT_SAMPLE_PERIOD = 100;
int curAccel = 0;
void getAccel();        // ISR prototype
LIS3DHSample sample;
LIS3DHI2C accel(Wire, 0, WKP);

// Car ESCs
Servo LESC;
Servo RESC;
int Lmotor = D2;
int Rmotor = D3;
int L_command = 0;
int R_command = 0;
int L_dir = 1;
int R_dir = 1;

// Fuzzy logic
Fuzzy* fuzzy = new Fuzzy();
float output;
String decision;

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

void accel_init() {
  LIS3DHConfig config;
  config.setAccelMode(LIS3DH::RATE_400_HZ);
  accel.setup(config);
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
  	Serial.begin(9600);	// *** need to modify before comp ***
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
  Serial.println("GO!");    
}

void fuzzy_init() {
  // low = far, high = close

  // INPUT: 1 of 4
  FuzzyInput* LL_input = new FuzzyInput(1);
  FuzzySet* LL_low = new FuzzySet(low1, low2, low3, low4);
  FuzzySet* LL_med = new FuzzySet(med1, med2, med3, med4);
  FuzzySet* LL_high = new FuzzySet(high1, high2, high3, high4);
  LL_input->addFuzzySet(LL_low);
  LL_input->addFuzzySet(LL_med);
  LL_input->addFuzzySet(LL_high);
  fuzzy->addFuzzyInput(LL_input);

  // INPUT: 2 of 4
  FuzzyInput* LM_input = new FuzzyInput(2);
  FuzzySet* LM_low = new FuzzySet(low1, low2, low3, low4);
  FuzzySet* LM_med = new FuzzySet(med1, med2, med3, med4);
  FuzzySet* LM_high = new FuzzySet(high1, high2, high3, high4);
  LM_input->addFuzzySet(LM_low);
  LM_input->addFuzzySet(LM_med);
  LM_input->addFuzzySet(LM_high);
  fuzzy->addFuzzyInput(LM_input);

  // INPUT: 3 of 4
  FuzzyInput* RM_input = new FuzzyInput(3);
  FuzzySet* RM_low = new FuzzySet(low1, low2, low3, low4);
  FuzzySet* RM_med = new FuzzySet(med1, med2, med3, med4);
  FuzzySet* RM_high = new FuzzySet(high1, high2, high3, high4);
  RM_input->addFuzzySet(RM_low);
  RM_input->addFuzzySet(RM_med);
  RM_input->addFuzzySet(RM_high);
  fuzzy->addFuzzyInput(RM_input);

  // INPUT: 4 of 4
  FuzzyInput* RR_input = new FuzzyInput(4);
  FuzzySet* RR_low = new FuzzySet(low1, low2, low3, low4);
  FuzzySet* RR_med = new FuzzySet(med1, med2, med3, med4);
  FuzzySet* RR_high = new FuzzySet(high1, high2, high3, high4);
  RR_input->addFuzzySet(RR_low);
  RR_input->addFuzzySet(RR_med);
  RR_input->addFuzzySet(RR_high);
  fuzzy->addFuzzyInput(RR_input);

  // OUTPUT: 1 of 1 (Test 1 *********************************)
  FuzzyOutput* drive_state = new FuzzyOutput(1);
  FuzzySet* full_left = new FuzzySet(0, 5, 15, 20);
  FuzzySet* small_left = new FuzzySet(25, 30, 35, 40);
  FuzzySet* center = new FuzzySet(45, 50, 55, 60);
  FuzzySet* small_right = new FuzzySet(65, 70, 75, 80);
  FuzzySet* full_right = new FuzzySet(85, 90, 95, 100);
  drive_state->addFuzzySet(full_left);
  drive_state->addFuzzySet(small_left);
  drive_state->addFuzzySet(center);
  drive_state->addFuzzySet(small_right);
  drive_state->addFuzzySet(full_right);
  fuzzy->addFuzzyOutput(drive_state);

  // Building Left FuzzyRuleAntecedents (ALL COMBINATIONS)
  FuzzyRuleAntecedent* left_low_high = new FuzzyRuleAntecedent();
  left_low_high->joinWithAND(LL_low, LM_high);
  FuzzyRuleAntecedent* left_med_high = new FuzzyRuleAntecedent();
  left_med_high->joinWithAND(LL_med, LM_high);
  FuzzyRuleAntecedent* left_low_med = new FuzzyRuleAntecedent();
  left_low_med->joinWithAND(LL_low, LM_med);
  FuzzyRuleAntecedent* left_med_med = new FuzzyRuleAntecedent();
  left_med_med->joinWithAND(LL_med, LM_med);
  FuzzyRuleAntecedent* left_high_high = new FuzzyRuleAntecedent();
  left_high_high->joinWithAND(LL_high, LM_high);
  FuzzyRuleAntecedent* left_high_med = new FuzzyRuleAntecedent();
  left_high_med->joinWithAND(LL_high, LM_med);
  FuzzyRuleAntecedent* left_med_low = new FuzzyRuleAntecedent();
  left_med_low->joinWithAND(LL_med, LM_low);
  FuzzyRuleAntecedent* left_high_low = new FuzzyRuleAntecedent();
  left_high_low->joinWithAND(LL_high, LM_low);
  FuzzyRuleAntecedent* left_low_low = new FuzzyRuleAntecedent();
  left_low_low->joinWithAND(LL_low, LM_low);

  // Building Right FuzzyRuleAntecedents
  FuzzyRuleAntecedent* right_high_low = new FuzzyRuleAntecedent();
  right_high_low->joinWithAND(RM_high, RR_low);
  FuzzyRuleAntecedent* right_high_med = new FuzzyRuleAntecedent();
  right_high_med->joinWithAND(RM_high, RR_med);
  FuzzyRuleAntecedent* right_med_low = new FuzzyRuleAntecedent();
  right_med_low->joinWithAND(RM_med, RR_low);
  FuzzyRuleAntecedent* right_low_med = new FuzzyRuleAntecedent();
  right_low_med->joinWithAND(RM_low, RR_med);
  FuzzyRuleAntecedent* right_low_low = new FuzzyRuleAntecedent();
  right_low_low->joinWithAND(RM_low, RR_low);
  FuzzyRuleAntecedent* right_med_med = new FuzzyRuleAntecedent();
  right_med_med->joinWithAND(RM_med, RR_med);
  FuzzyRuleAntecedent* right_low_high = new FuzzyRuleAntecedent();
  right_low_high->joinWithAND(RM_low, RR_high);
  FuzzyRuleAntecedent* right_high_high = new FuzzyRuleAntecedent();
  right_high_high->joinWithAND(RM_high, RR_high);
  FuzzyRuleAntecedent* right_med_high = new FuzzyRuleAntecedent();
  right_med_high->joinWithAND(RM_med, RR_high);

  // Building drive FuzzyRuleConsequents (Test 1 *********************************)
  // NOTE: you can add multiple outputs to 1 consequent
  FuzzyRuleConsequent* drive_center = new FuzzyRuleConsequent();
  drive_center->addOutput(center);
  FuzzyRuleConsequent* drive_small_left = new FuzzyRuleConsequent();
  drive_small_left->addOutput(small_left);  
  FuzzyRuleConsequent* drive_full_left = new FuzzyRuleConsequent();
  drive_full_left->addOutput(full_left);
  FuzzyRuleConsequent* drive_full_right = new FuzzyRuleConsequent();
  drive_full_right->addOutput(full_right);
  FuzzyRuleConsequent* drive_small_right = new FuzzyRuleConsequent();
  drive_small_right->addOutput(small_right);

  // Building Complete FuzzyRuleAntedecents (Test 1 *********************************)
  // Combining (2) Left and (2) Right antecedents, merging with (1) drive consequent
  // And adding the FuzzyRules
  FuzzyRuleAntecedent* LHHL = new FuzzyRuleAntecedent();
  LHHL->joinWithAND(left_low_high, right_high_low);
  FuzzyRule* fr1 = new FuzzyRule(1, LHHL, drive_center);
  fuzzy->addFuzzyRule(fr1);

  FuzzyRuleAntecedent* MHHL = new FuzzyRuleAntecedent();
  MHHL->joinWithAND(left_med_high, right_high_low);
  FuzzyRule* fr2 = new FuzzyRule(2, MHHL, drive_center);
  fuzzy->addFuzzyRule(fr2); 

  FuzzyRuleAntecedent* LHHM = new FuzzyRuleAntecedent();
  LHHM->joinWithAND(left_low_high, right_high_med);
  FuzzyRule* fr3 = new FuzzyRule(3, LHHM, drive_center);
  fuzzy->addFuzzyRule(fr3);

  FuzzyRuleAntecedent* LMML = new FuzzyRuleAntecedent();
  LMML->joinWithAND(left_low_med, right_med_low);
  FuzzyRule* fr4 = new FuzzyRule(4, LMML, drive_center);
  fuzzy->addFuzzyRule(fr4);

  FuzzyRuleAntecedent* MMMM = new FuzzyRuleAntecedent();
  MMMM->joinWithAND(left_med_med, right_med_med);
  FuzzyRule* fr5 = new FuzzyRule(5, MMMM, drive_center);
  fuzzy->addFuzzyRule(fr5);

  FuzzyRuleAntecedent* HHLL = new FuzzyRuleAntecedent();
  HHLL->joinWithAND(left_high_high, right_low_low);
  FuzzyRule* fr6 = new FuzzyRule(6, HHLL, drive_small_left);
  fuzzy->addFuzzyRule(fr6);

  FuzzyRuleAntecedent* HHML = new FuzzyRuleAntecedent();
  HHML->joinWithAND(left_high_high, right_med_low);
  FuzzyRule* fr7 = new FuzzyRule(6, HHML, drive_small_left);
  fuzzy->addFuzzyRule(fr7);

  FuzzyRuleAntecedent* HHMM = new FuzzyRuleAntecedent();
  HHMM->joinWithAND(left_high_high, right_med_med);
  FuzzyRule* fr8 = new FuzzyRule(8, HHMM, drive_small_left);
  fuzzy->addFuzzyRule(fr8);

  FuzzyRuleAntecedent* MHMM = new FuzzyRuleAntecedent();
  MHMM->joinWithAND(left_med_high, right_med_med);
  FuzzyRule* fr9 = new FuzzyRule(9, MHMM, drive_small_left);
  fuzzy->addFuzzyRule(fr9);

  FuzzyRuleAntecedent* MHML = new FuzzyRuleAntecedent();
  MHML->joinWithAND(left_med_high, right_med_low);
  FuzzyRule* fr10 = new FuzzyRule(10, MHML, drive_small_left);
  fuzzy->addFuzzyRule(fr10);

  FuzzyRuleAntecedent* MHLL = new FuzzyRuleAntecedent();
  MHLL->joinWithAND(left_med_high, right_low_low);
  FuzzyRule* fr11 = new FuzzyRule(11, MHLL, drive_small_left);
  fuzzy->addFuzzyRule(fr11);

  FuzzyRuleAntecedent* MMML = new FuzzyRuleAntecedent();
  MMML->joinWithAND(left_med_med, right_med_low);
  FuzzyRule* fr12 = new FuzzyRule(12, MMML, drive_small_left);
  fuzzy->addFuzzyRule(fr12);

  FuzzyRuleAntecedent* MMLL = new FuzzyRuleAntecedent();
  MMLL->joinWithAND(left_med_med, right_low_low);
  FuzzyRule* fr13 = new FuzzyRule(13, MMLL, drive_small_left);
  fuzzy->addFuzzyRule(fr13);

  FuzzyRuleAntecedent* HMLL = new FuzzyRuleAntecedent();
  HMLL->joinWithAND(left_high_med, right_low_low);
  FuzzyRule* fr14 = new FuzzyRule(14, HMLL, drive_small_left);
  fuzzy->addFuzzyRule(fr14);

  FuzzyRuleAntecedent* MLLL = new FuzzyRuleAntecedent();
  MLLL->joinWithAND(left_med_low, right_low_low);
  FuzzyRule* fr15 = new FuzzyRule(15, MLLL, drive_small_left);
  fuzzy->addFuzzyRule(fr15);

  FuzzyRuleAntecedent* HLLL = new FuzzyRuleAntecedent();
  HLLL->joinWithAND(left_high_low, right_low_low);
  FuzzyRule* fr16 = new FuzzyRule(16, HLLL, drive_full_left);
  fuzzy->addFuzzyRule(fr16);

  FuzzyRuleAntecedent* LLLH = new FuzzyRuleAntecedent();
  LLLH->joinWithAND(left_low_low, right_low_high);
  FuzzyRule* fr17 = new FuzzyRule(17, LLLH, drive_full_right);
  fuzzy->addFuzzyRule(fr17);

  FuzzyRuleAntecedent* LLHH = new FuzzyRuleAntecedent();
  LLHH->joinWithAND(left_low_low, right_high_high);
  FuzzyRule* fr18 = new FuzzyRule(18, LLHH, drive_small_right);
  fuzzy->addFuzzyRule(fr18);

  FuzzyRuleAntecedent* LMHH = new FuzzyRuleAntecedent();
  LMHH->joinWithAND(left_low_med, right_high_high);
  FuzzyRule* fr19 = new FuzzyRule(19, LMHH, drive_small_right);
  fuzzy->addFuzzyRule(fr19);

  FuzzyRuleAntecedent* MMHH = new FuzzyRuleAntecedent();
  MMHH->joinWithAND(left_med_med, right_high_high);
  FuzzyRule* fr20 = new FuzzyRule(20, MMHH, drive_small_right);
  fuzzy->addFuzzyRule(fr20);

  FuzzyRuleAntecedent* MMHM = new FuzzyRuleAntecedent();
  MMHM->joinWithAND(left_med_med, right_high_med);
  FuzzyRule* fr21 = new FuzzyRule(21, MMHM, drive_small_right);
  fuzzy->addFuzzyRule(fr21);

  FuzzyRuleAntecedent* LMHM = new FuzzyRuleAntecedent();
  LMHM->joinWithAND(left_low_med, right_high_med);
  FuzzyRule* fr22 = new FuzzyRule(22, LMHM, drive_small_right);
  fuzzy->addFuzzyRule(fr22);

  FuzzyRuleAntecedent* LLHM = new FuzzyRuleAntecedent();
  LLHM->joinWithAND(left_low_low, right_high_med);
  FuzzyRule* fr23 = new FuzzyRule(23, LLHM, drive_small_right);
  fuzzy->addFuzzyRule(fr23);

  FuzzyRuleAntecedent* LMMM = new FuzzyRuleAntecedent();
  LMMM->joinWithAND(left_low_med, right_med_med);
  FuzzyRule* fr24 = new FuzzyRule(24, LMMM, drive_small_right);
  fuzzy->addFuzzyRule(fr24);

  FuzzyRuleAntecedent* LLMM = new FuzzyRuleAntecedent();
  LLMM->joinWithAND(left_low_low, right_med_med);
  FuzzyRule* fr25 = new FuzzyRule(25, LLMM, drive_small_right);
  fuzzy->addFuzzyRule(fr25);

  FuzzyRuleAntecedent* LLMH = new FuzzyRuleAntecedent();
  LLMH->joinWithAND(left_low_low, right_med_high);
  FuzzyRule* fr26 = new FuzzyRule(26, LLMH, drive_small_right);
  fuzzy->addFuzzyRule(fr26);

  FuzzyRuleAntecedent* LLLM = new FuzzyRuleAntecedent();
  LLLM->joinWithAND(left_low_low, right_low_med);
  FuzzyRule* fr27 = new FuzzyRule(27, LLLM, drive_small_right);
  fuzzy->addFuzzyRule(fr27);

  FuzzyRuleAntecedent* LLLL = new FuzzyRuleAntecedent();
  LLLL->joinWithAND(left_low_low, right_low_low);
  FuzzyRule* fr28 = new FuzzyRule(28, LLLL, drive_center);	// should it be search?
  fuzzy->addFuzzyRule(fr28);

  // Revisions
  FuzzyRuleAntecedent* LHLL = new FuzzyRuleAntecedent();
  LHLL->joinWithAND(left_low_high, right_low_low);
  FuzzyRule* fr29 = new FuzzyRule(29, LHLL, drive_small_left);
  fuzzy->addFuzzyRule(fr29);

  FuzzyRuleAntecedent* LMLL = new FuzzyRuleAntecedent();
  LMLL->joinWithAND(left_low_med, right_low_low);
  FuzzyRule* fr30 = new FuzzyRule(30, LMLL, drive_small_left);
  fuzzy->addFuzzyRule(fr30);

  FuzzyRuleAntecedent* LLML = new FuzzyRuleAntecedent();
  LLML->joinWithAND(left_low_low, right_med_low);
  FuzzyRule* fr31 = new FuzzyRule(31, LLML, drive_small_right);
  fuzzy->addFuzzyRule(fr31);

  FuzzyRuleAntecedent* LLHL = new FuzzyRuleAntecedent();
  LLHL->joinWithAND(left_low_low, right_high_low);
  FuzzyRule* fr32 = new FuzzyRule(32, LLHL, drive_small_right);
  fuzzy->addFuzzyRule(fr32);
}

void setup() {
	tof_init();			// ToF and I2C
	accel_init();		// accelerometer
	others_init();		// line, remote, esc, ***printing***
	interrupt_init();	// interrupts for lines and remote
	ESC_init();			// Car ESCs
	fuzzy_init();		// Fuzzy library************

	RGB.control(true); 	// take control of the on-board LED for debugging

	robot_init();
	line_init();		// initialize line variables
}

// -----------------------------------------------------------
// ------------------Runtime functions------------------------
// -----------------------------------------------------------

void stop() {
  	LESC.writeMicroseconds(1500);
  	RESC.writeMicroseconds(1500);
}

void getAccel() {
  accel.getSample(sample);
  curAccel = sample.x;
}

void getToF() {
	RR_distance = sensor0.readRangeContinuousMillimeters();
	RM_distance = sensor1.readRangeContinuousMillimeters();
	LM_distance = sensor2.readRangeContinuousMillimeters();
	LL_distance = sensor3.readRangeContinuousMillimeters();
	// if (sensor0.timeoutOccurred() || sensor1.timeoutOccurred() || sensor2.timeoutOccurred() || sensor3.timeoutOccurred()) { Serial.print(" SENSOR TIMEOUT"); }
}

void doFuzzy() {
  fuzzy->setInput(1, LL_distance);
  fuzzy->setInput(2, LM_distance);
  fuzzy->setInput(3, RM_distance);
  fuzzy->setInput(4, RR_distance);
  fuzzy->fuzzify();
  output = fuzzy->defuzzify(1);

	if((output >= 0) && (output < 20)) {
		decision = "Full Left";
		RGB.color(0, 0, 255);

		L_command = v_full_slow;
		R_command = v_full_fast;
		L_dir = 1;
		R_dir = 1;
	} else if((output >= 20) && (output < 40)) {
		decision = "Small Left";
		RGB.color(0, 128, 128);

 		L_command = v_small_slow;
		R_command = v_small_fast;
		L_dir = 1;
		R_dir = 1;
  } else if((output >= 40) && (output < 60)) {
	  decision = "Center";
	  RGB.color(0, 255, 0);

		L_command = v_center;
		R_command = v_center;
		L_dir = 1;
		R_dir = 1;
  } else if((output >= 60) && (output < 80)) {
	  decision = "Small Right";
	  RGB.color(128, 128, 0);

		L_command = v_small_fast;
		R_command = v_small_slow;
		L_dir = 1;
		R_dir = 1;
  } else if((output >= 80) && (output < 100)) {
	  decision = "Full Right";
	  RGB.color(255, 0, 0);

		L_command = v_full_fast;
		R_command = v_full_slow;
		L_dir = 1;
		R_dir = 1;
  }
}

void checkSwitch() {
  	if(RSflag == LOW) {
  		stop();
  		Serial.print("STOPPED");
  		while(true);
  	}
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

void movement(int state) {
	// right now, there are only states 0, 1, and 10***
	if(state == 0) {			// move forward
  		L_command = line_fwd;
  		R_command = line_fwd;
  		L_dir = 1;
  		R_dir = 1;
      Serial.println("Back triggered, moving forward");
	} else if(state == 10) {
	    if (cur - prevFlag < nudge) {			// go backwards a 'nudge'
	  		L_command = line_rev;
	  		R_command = line_rev;
	  		L_dir = 0;
	  		R_dir = 0;
        Serial.println("Moving backwards a nudge");
	    }
	    else if (cur - prevFlag < degrees180) {	// turn cw 180
	  		L_command = line_180;
	  		R_command = line_180;
	  		R_dir = 0;
	  		L_dir = 1;
        Serial.println("Turning 180");
	    }
	    else {									// reset line flags & detection flag
        FLflag = true;						// only when movement is FINISHED
        FRflag = true;
	      BLflag = true;
	      BRflag = true;
	      prevFlagSet = false;
        Serial.println("FINISHED DEALING WITH THE LINE");
	    }
	    // moving = true;
	} else {					// stop
  		L_command = 0;
  		R_command = 0;
  		R_dir = 1;
  		L_dir = 1;
      Serial.println("Stopped before death");
	}
}

void checkLine() {
  if (!FLflag || !FRflag || prevFlagSet) {				// if front line triggered
    if (!prevFlagSet) {					// and if this is the FIRST detection of the line
      RGB.color(255, 255, 255);
      prevFlag = cur;					// reset the turn timer
      prevFlagSet = true;				// ensures timer is reset only ONCE
      movement(1);						// stop before you fall off
    }
    movement(10);						// begin/continue the turn sequence
  } else if (!BRflag || !BLflag) {		// if back line triggered, move forward
    RGB.color(255, 255, 255);
    movement(0);

    // prevFlagSet = true;

  } else if(!prevFlagSet) {  // if a line hasn't been seen, continue fuzzy
    Serial.println("Doing Fuzzy");
    // prevFlagSet = false;	
  }
}

void loop(){
	checkLine();

  // Serial.print(decision);
  // Serial.print(" | ");

  // Serial.print("RR: ");
  // Serial.print(RR_distance);
  // Serial.print(" | ");
  // Serial.print("RM: ");
  // Serial.print(RM_distance);
  // Serial.print(" | ");
  // Serial.print("LM: ");
  // Serial.print(LM_distance);
  // Serial.print(" | ");
  // Serial.print("LL: ");
  // Serial.print(LL_distance);

	if (!prevFlagSet) {	// if dealing with line don't do fuzzy
		getToF();
		doFuzzy();
	}

  cur = millis();           // update timer

	checkSwitch();

  move(1, R_command, R_dir);
  move(2, L_command, L_dir);
}