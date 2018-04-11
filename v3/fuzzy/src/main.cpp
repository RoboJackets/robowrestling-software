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

VL53L0X sensor0;
VL53L0X sensor1;
VL53L0X sensor2;
VL53L0X sensor3;

int LL_distance;
int LM_distance;
int RM_distance;
int RR_distance;

int FL = D7;    // AUX BOARD SWITCHED FL and FR up
int FR = A4;    // A5 does not support attachInterrupt, so jump A5 to D7 on the board, also cut INT line
int BL = D5;
int BR = D6;

int RS = D4;

Servo LESC;
Servo RESC;
int Lmotor = D2;
int Rmotor = D3;
int L_command = 1500;
int R_command = 1500;

boolean FLflag = true; // active low
boolean FRflag = true;
boolean BLflag = true;
boolean BRflag = true;

boolean RSflag = false;

Fuzzy* fuzzy = new Fuzzy();

SYSTEM_THREAD(ENABLED);
// Try to print on web console**************************
SYSTEM_MODE(MANUAL);

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
  config.setAccelMode(LIS3DH::RATE_400_HZ);

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
}

void ESC_init() {
	// Necessary for Servo objects
  	LESC.attach(Lmotor);
  	RESC.attach(Rmotor);
  	// Write stop command
  	LESC.writeMicroseconds(1500);
  	RESC.writeMicroseconds(1500);
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
}

void setup() {
	tof_init();			// ToF and I2C
	accel_init();		// accelerometer
	others_init();		// line, remote, esc, ***printing***
	interrupt_init();	// interrupts for lines and remote
	ESC_init();			// Car ESCs

  // ***Set up web*** ****************************
  // register cloud variables
	// Particle.variable("distance", distance);
	// Particle.variable("Left_ESC", L_command);
	// Particle.variable("Right_ESC", R_command);
	// *********************************************

  while(!RSflag) {  // initial LOW
    Serial.println("Waiting for Start");
    // Particle.publish("Waiting for Start");
  }
  Serial.println("Starting in 5 seconds...");
  // Particle.publish("Starting in 5 seconds...");
  delay(5000);
  Serial.println("GO!");
  // Particle.publish("GO!");

  // ***********TIME FUZZY**********************************
  unsigned long currentTime = millis();
  fuzzy_init();		// Fuzzy library************
  Serial.println(millis() - currentTime);
  // Measured: 1ms to initialize.
}

void loop(){
	// sensorx.readRangeContinuousMillimeters();
	LL_distance = sensor0.readRangeContinuousMillimeters();
	LM_distance = sensor1.readRangeContinuousMillimeters();
	RM_distance = sensor2.readRangeContinuousMillimeters();
	RR_distance = sensor3.readRangeContinuousMillimeters();

	if (sensor0.timeoutOccurred() || sensor1.timeoutOccurred() || sensor2.timeoutOccurred() || sensor3.timeoutOccurred()) { Serial.print(" SENSOR TIMEOUT"); }
	
	// pre-processing (changing 8192 to low4)
	if(LL_distance > 2000) { 
		LL_distance = low4;
	}
	if(LM_distance > 2000) { 
		LL_distance = low4;
	}
	if(RM_distance > 2000) { 
		LL_distance = low4;
	}
	if(RR_distance > 2000) { 
		LL_distance = low4;
	}

	// xESC.writeMicroseconds(yyyy);
	// ***TBD***
  
  	// FUZZY **************************************************

  	fuzzy->setInput(1, LL_distance);
  	fuzzy->setInput(2, LM_distance);
  	fuzzy->setInput(3, RM_distance);
  	fuzzy->setInput(4, RR_distance);
  
  	// CURRENT ISSUE: 8192, the max value that the ToF defaults to when it doesn't see
  	// is hard to process in the fuzzy logic since the highest "seen" value is ~1250
  	fuzzy->fuzzify();
  	float output = fuzzy->defuzzify(1);

  	Serial.print("OUTPUT: ");
  	Serial.print(output);
  	Serial.print(" | ");

  	Serial.print("sensor 0:");
  	Serial.print(LL_distance);
  	Serial.print(" | ");
  	Serial.print("sensor 1:");
  	Serial.print(LM_distance);
  	Serial.print(" | ");
  	Serial.print("sensor 2:");
  	Serial.print(RM_distance);
  	Serial.print(" | ");
  	Serial.print("sensor 3:");
  	Serial.println(RR_distance);
  	delay(100);

  	// FUZZY ***********************************************


  	// obligatory sampling from accelerometer
  	LIS3DHSample sample;
  	if(!accel.getSample(sample)) {
  		Serial.println("no sample"); // ********************************
  		// Particle.publish("no sample");
  	}

  	if(RSflag == HIGH) {
  		L_command = 1500;
    	R_command = 1500;
  	}

  	LESC.writeMicroseconds(L_command);
  	RESC.writeMicroseconds(R_command);
}