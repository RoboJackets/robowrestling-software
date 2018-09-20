//
// Created by Logan Schick on 9/6/2018.
//

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

#if !defined(PARTICLE)
#  include <Wire.h>
#endif

#include <sensors.h>

#include <movement.h>

#include <logic.h>

VL53L0X sensor0;
VL53L0X sensor1;
VL53L0X sensor2;
VL53L0X sensor3;
int L_command = 0;
int R_command = 0;
int L_dir = 1;
int R_dir = 1;
Fuzzy* fuzzy = new Fuzzy();
uint16_t RR_distance = sensor0.readRangeContinuousMillimeters();
uint16_t RM_distance = sensor1.readRangeContinuousMillimeters();
uint16_t LM_distance = sensor2.readRangeContinuousMillimeters();
uint16_t LL_distance = sensor3.readRangeContinuousMillimeters();
float output = 0;
String decision = "";

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
        // Serial.print("STOPPED");
        while(true);
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
    } else if ((!BRflag || !BLflag) && !prevFlagSet) {		// if back line triggered, move forward
        RGB.color(255, 255, 255);
        movement(0);

        // prevFlagSet = true;

    } else if(!prevFlagSet) {  // if a line hasn't been seen, continue fuzzy
        // Serial.println("Doing Fuzzy");
        // prevFlagSet = false;
    }
}
