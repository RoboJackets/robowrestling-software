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

#include <movement.h>

#include <logic.h>

#include <sensors.h>

#include <init.h>

#include <VL53L0X.h>

#if !defined(PARTICLE)
#  include <Wire.h>
#endif

#include <sensors.h>

#include <init.h>

// Particle Photon settings
SYSTEM_THREAD(ENABLED);
SYSTEM_MODE(MANUAL);

void setup() {
    tof_init();			// ToF and I2C

    // accel_init();		// accelerometer NOT USED

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

void loop(){
  cur = millis();           // update timer

  if (start) {
    startUp();
  }

  if (!start) {
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
  }


  // Serial.print("cur: ");
  // Serial.println(cur);
  // Serial.print("prevFlag: ");
  // Serial.println(prevFlag);
  // Serial.println(start);

	checkSwitch();

  move(1, R_command, R_dir);
  move(2, L_command, L_dir);
}
