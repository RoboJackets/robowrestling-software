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
/**Add 2 more sensors here
*  uint16_t RS_distance = sensor4.readRangeContinuousMillimeters();
*  uint16_t LS_distance = sensor5.readRangeContinuousMillimeters();
*/
float output = 0;
String decision = "";

//Setting up all the fuzzy logic cases so we can decide how much to turn
//Need to increase the number of inputs to 6 and changing the output and antecedent stuff
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

    //INPUT: 5 of 4
    FuzzyInput* RS_input = new FuzzyInput(4);
    FuzzySet* RS_low = new FuzzySet(low1, low2, low3, low4);
    FuzzySet* RS_med = new FuzzySet(med1, med2, med3, med4);
    FuzzySet* RS_high = new FuzzySet(high1, high2, high3, high4);
    RS_input->addFuzzySet(RS_low);
    RS_input->addFuzzySet(RS_med);
    RS_input->addFuzzySet(RS_high);
    fuzzy->addFuzzyInput(RS_input);

    //INPUT: 6 of 4
    FuzzyInput* LS_input = new FuzzyInput(4);
    FuzzySet* LS_low = new FuzzySet(low1, low2, low3, low4);
    FuzzySet* LS_med = new FuzzySet(med1, med2, med3, med4);
    FuzzySet* LS_high = new FuzzySet(high1, high2, high3, high4);
    LS_input->addFuzzySet(LS_low);
    LS_input->addFuzzySet(LS_med);
    LS_input->addFuzzySet(LS_high);
    fuzzy->addFuzzyInput(LS_input);

    // OUTPUT: 1 of 1 (Test 1 *********************************)
    FuzzyOutput* drive_state = new FuzzyOutput(1);
    FuzzySet* point_turn_left = new FuzzySet( , , , ); Readjust others to include 3.57 per
    FuzzySet* full_left = new FuzzySet(0, 5, 15, 20);
    FuzzySet* small_left = new FuzzySet(25, 30, 35, 40);
    FuzzySet* center = new FuzzySet(45, 50, 55, 60);
    FuzzySet* small_right = new FuzzySet(65, 70, 75, 80);
    FuzzySet* full_right = new FuzzySet(85, 90, 95, 100);
    FuzzySet* point_turn_right = new FuzzySet( , , , ); Readjust others to include 3.57 per
    drive_state->addFuzzySet(point_turn_left);
    drive_state->addFuzzySet(full_left);
    drive_state->addFuzzySet(small_left);
    drive_state->addFuzzySet(center);
    drive_state->addFuzzySet(small_right);
    drive_state->addFuzzySet(full_right);
    drive_state->addFuzzySet(point_turn_right);
    fuzzy->addFuzzyOutput(drive_state);

    // Building LeftLM FuzzyRuleAntecedents (ALL COMBINATIONS)
    FuzzyRuleAntecedent* leftlm_low_high = new FuzzyRuleAntecedent();
    leftlm_low_high->joinWithAND(LL_low, LM_high);
    FuzzyRuleAntecedent* leftlm_med_high = new FuzzyRuleAntecedent();
    leftlm_med_high->joinWithAND(LL_med, LM_high);
    FuzzyRuleAntecedent* leftlm_low_med = new FuzzyRuleAntecedent();
    leftlm_low_med->joinWithAND(LL_low, LM_med);
    FuzzyRuleAntecedent* leftlm_med_med = new FuzzyRuleAntecedent();
    leftlm_med_med->joinWithAND(LL_med, LM_med);
    FuzzyRuleAntecedent* leftlm_high_high = new FuzzyRuleAntecedent();
    leftlm_high_high->joinWithAND(LL_high, LM_high);
    FuzzyRuleAntecedent* leftlm_high_med = new FuzzyRuleAntecedent();
    leftlm_high_med->joinWithAND(LL_high, LM_med);
    FuzzyRuleAntecedent* leftlm_med_low = new FuzzyRuleAntecedent();
    leftlm_med_low->joinWithAND(LL_med, LM_low);
    FuzzyRuleAntecedent* leftlm_high_low = new FuzzyRuleAntecedent();
    leftlm_high_low->joinWithAND(LL_high, LM_low);
    FuzzyRuleAntecedent* leftlm_low_low = new FuzzyRuleAntecedent();
    leftlm_low_low->joinWithAND(LL_low, LM_low);

    //Building LeftSLM Part 1: LS_low
    FuzzyRuleAntecedent* left_low_low_high = new FuzzyRuleAntecedent();
    left_low_low_high->joinWithAND(LS_low, leftlm_low_high);
    FuzzyRuleAntecedent* left_low_med_high = new FuzzyRuleAntecedent();
    left_low_med_high->joinWithAND(LS_low, leftlm_med_high);
    FuzzyRuleAntecedent* left_low_low_med = new FuzzyRuleAntecedent();
    left_low_low_med->joinWithAND(LS_low, leftlm_low_med);
    FuzzyRuleAntecedent* left_low_med_med = new FuzzyRuleAntecedent();
    left_low_med_med->joinWithAND(LS_low, leftlm_med_med);
    FuzzyRuleAntecedent* left_low_high_high = new FuzzyRuleAntecedent();
    left_low_high_high->joinWithAND(LS_low, leftlm_high_high);
    FuzzyRuleAntecedent* left_low_high_med = new FuzzyRuleAntecedent();
    left_low_high_med->joinWithAND(LS_low, leftlm_high_med);
    FuzzyRuleAntecedent* left_low_med_low = new FuzzyRuleAntecedent();
    left_low_med_low->joinWithAND(LS_low, leftlm_med_low);
    FuzzyRuleAntecedent* left_low_high_low = new FuzzyRuleAntecedent();
    left_low_high_low->joinWithAND(LS_low, leftlm_high_low);
    FuzzyRuleAntecedent* left_low_low_low = new FuzzyRuleAntecedent();
    left_low_low_low->joinWithAND(LS_low, leftlm_low_low);

    //Building LeftSL FuzzyRuleAntecedents
    FuzzyRuleAntecedent* leftsl_high_low = new FuzzyRuleAntecedent();
    leftsl_high_low->joinWithAND(LS_high, LL_low);
    FuzzyRuleAntecedent* leftsl_med_med = new FuzzyRuleAntecedent();
    leftsl_med_med->joinWithAND(LS_med, LL_med);
    FuzzyRuleAntecedent* leftsl_med_high = new FuzzyRuleAntecedent();
    leftsl_med_high->joinWithAND(LS_med, LL_high);
    FuzzyRuleAntecedent* leftsl_med_low = new FuzzyRuleAntecedent();
    leftsl_med_low->joinWithAND(LS_med, LS_low);

    //Building LeftSLM Part 2: Adding M
    FuzzyRuleAntecedent* left_high_low_low = new FuzzyRuleAntecedent();
    left_high_low_low->joinWithAND(leftsl_high_low, LM_low);
    FuzzyRuleAntecedent* left_med_med_low = new FuzzyRuleAntecedent();
    left_med_med_low->joinWithAND(leftsl_med_med, LM_low);
    FuzzyRuleAntecedent* left_med_high_low = new FuzzyRuleAntecedent();
    left_med_high_low->joinWithAND(leftsl_med_high, LM_low);
    FuzzyRuleAntecedent* left_med_med_med = new FuzzyRuleAntecedent();
    left_med_med_med->joinWithAND(leftsl_med_med, LM_med);
    FuzzyRuleAntecedent* left_med_low_low = new FuzzyRuleAntecedent();
    left_med_low_low->joinWithAND(leftsl_med_low, LM_low);
    FuzzyRuleAntecedent* left_med_med_high = new FuzzyRuleAntecedent();
    left_med_med_high->joinWithAND(leftsl_med_med, LM_high);
    FuzzyRuleAntecedent* left_med_high_high = new FuzzyRuleAntecedent();
    left_med_high_high->joinWithAND(leftsl_med_high, LM_high);


    // Building RightMR FuzzyRuleAntecedents
    FuzzyRuleAntecedent* rightmr_high_low = new FuzzyRuleAntecedent();
    rightmr_high_low->joinWithAND(RM_high, RR_low);
    FuzzyRuleAntecedent* rightmr_high_med = new FuzzyRuleAntecedent();
    rightmr_high_med->joinWithAND(RM_high, RR_med);
    FuzzyRuleAntecedent* rightmr_med_low = new FuzzyRuleAntecedent();
    rightmr_med_low->joinWithAND(RM_med, RR_low);
    FuzzyRuleAntecedent* rightmr_low_med = new FuzzyRuleAntecedent();
    rightmr_low_med->joinWithAND(RM_low, RR_med);
    FuzzyRuleAntecedent* rightmr_low_low = new FuzzyRuleAntecedent();
    rightmr_low_low->joinWithAND(RM_low, RR_low);
    FuzzyRuleAntecedent* rightmr_med_med = new FuzzyRuleAntecedent();
    rightmr_med_med->joinWithAND(RM_med, RR_med);
    FuzzyRuleAntecedent* rightmr_low_high = new FuzzyRuleAntecedent();
    rightmr_low_high->joinWithAND(RM_low, RR_high);
    FuzzyRuleAntecedent* rightmr_high_high = new FuzzyRuleAntecedent();
    rightmr_high_high->joinWithAND(RM_high, RR_high);
    FuzzyRuleAntecedent* rightmr_med_high = new FuzzyRuleAntecedent();
    rightmr_med_high->joinWithAND(RM_med, RR_high);

    //Building RightMRS Part 1: RS_low
    FuzzyRuleAntecedent* right_high_low_low = new FuzzyRuleAntecedent();
    right_high_low_low->joinWithAND(rightmr_high_low, RS_low);
    FuzzyRuleAntecedent* rightmr_high_med_low = new FuzzyRuleAntecedent();
    right_high_med_low->joinWithAND(rightmr_high_med, RS_low);
    FuzzyRuleAntecedent* right_med_low_low = new FuzzyRuleAntecedent();
    right_med_low_low->joinWithAND(righmr_med_low, RS_low);
    FuzzyRuleAntecedent* right_low_med_low = new FuzzyRuleAntecedent();
    right_low_med_low->joinWithAND(rightmr_low_med, RS_low);
    FuzzyRuleAntecedent* right_low_low_low = new FuzzyRuleAntecedent();
    right_low_low_low->joinWithAND(rightmr_low_low, RS_low);
    FuzzyRuleAntecedent* right_med_med_low = new FuzzyRuleAntecedent();
    right_med_med_low->joinWithAND(rightmr_med_med, RS_low);
    FuzzyRuleAntecedent* right_low_high_low = new FuzzyRuleAntecedent();
    right_low_high_low->joinWithAND(rightmr_low_high, RS_low);
    FuzzyRuleAntecedent* right_high_high_low = new FuzzyRuleAntecedent();
    right_high_high_low->joinWithAND(rightmr_high_high, RS_low);
    FuzzyRuleAntecedent* right_med_high_low = new FuzzyRuleAntecedent();
    rightmr_med_high_low->joinWithAND(rightmr_med_high, RS_low);

    //Building RightRS FuzzyRuleAntecedents
    FuzzyRuleAntecedent* rightrs_low_high = new FuzzyRuleAntecedent();
    rightrs_low_high->joinWithAND(RR_low, RS_high);
    FuzzyRuleAntecedent* rightrs_med_med = new FuzzyRuleAntecedent();
    rightrs_med_med->joinWithAND(RR_med, RS_med);
    FuzzyRuleAntecedent* rightrs_high_med = new FuzzyRuleAntecedent();
    rightrs_high_med->joinWithAND(RR_high, RS_med);
    FuzzyRuleAntecedent* rightrs_low_med = new FuzzyRuleAntecedent();
    rightrs_low_med->joinWithAND(RR_low, RS_med);

    //Building RightMRS Part 2: Adding M
    FuzzyRuleAntecedent* right_low_low_high = new FuzzyRuleAntecedent();
    rightrs_high_low->joinWithAND(RM_low, rightrs_high_low);
    FuzzyRuleAntecedent* right_low_med_med = new FuzzyRuleAntecedent();
    right_low_med_med->joinWithAND(RM_low, rightrs_med_med);
    FuzzyRuleAntecedent* right_low_high_med = new FuzzyRuleAntecedent();
    right_low_high_med->joinWithAND(RM_low, rightrs_high_med);
    FuzzyRuleAntecedent* right_med_med_med = new FuzzyRuleAntecedent();
    right_med_med_med->joinWithAND(RM_med, rightrs_med_med);
    FuzzyRuleAntecedent* right_low_low_med = new FuzzyRuleAntecedent();
    right_low_low_med->joinWithAND(RM_low, rightrs_low_med);
    FuzzyRuleAntecedent* right_high_high_med = new FuzzyRuleAntecedent();
    right_high_high_med->joinWithAND(RM_high, rightrs_high_med);
    FuzzyRuleAntecedent* right_high_med_med = new FuzzyRuleAntecedent();
    right_high_med_med->joinWithAND(RM_high, rightrs_med_med);

    // Building drive FuzzyRuleConsequents (Test 1 *********************************)
    // NOTE: you can add multiple outputs to 1 consequent


    FuzzyRuleConsequent* drive_point_turn_left = new FuzzyRuleConsequent();
    drive_point_turn_left->addOutput(point_turn_left);
    FuzzyRuleConsequent* drive_full_left = new FuzzyRuleConsequent();
    drive_full_left->addOutput(full_left);
    FuzzyRuleConsequent* drive_small_left = new FuzzyRuleConsequent();
    drive_small_left->addOutput(small_left);
    FuzzyRuleConsequent* drive_center = new FuzzyRuleConsequent();
    drive_center->addOutput(center);
    FuzzyRuleConsequent* drive_small_right = new FuzzyRuleConsequent();
    drive_small_right->addOutput(small_right);
    FuzzyRuleConsequent* drive_full_right = new FuzzyRuleConsequent();
    drive_full_right->addOutput(full_right);
    FuzzyRuleConsequent* drive_point_turn_right = new FuzzyRuleConsequent();
    drive_point_turn_right->addOutput(point_turn_right);

    // Building Complete FuzzyRuleAntedecents (Test 1 *********************************)
    // Combining (2) Left and (2) Right antecedents, merging with (1) drive consequent
    // And adding the FuzzyRules
    FuzzyRuleAntecedent* LLHHLL = new FuzzyRuleAntecedent();
    LLHHLL->joinWithAND(left_low_low_high, right_high_low_low);
    FuzzyRule* fr1 = new FuzzyRule(1, LLHHLL, drive_center);
    fuzzy->addFuzzyRule(fr1);

    FuzzyRuleAntecedent* LMHHLL = new FuzzyRuleAntecedent();
    LMHHLL->joinWithAND(left_low_med_high, right_high_low_low);
    FuzzyRule* fr2 = new FuzzyRule(2, LMHHLL, drive_center);
    fuzzy->addFuzzyRule(fr2);

    FuzzyRuleAntecedent* LLHHML = new FuzzyRuleAntecedent();
    LLHHML->joinWithAND(left_low_low_high, right_high_med_low);
    FuzzyRule* fr3 = new FuzzyRule(3, LLHHML, drive_center);
    fuzzy->addFuzzyRule(fr3);

    FuzzyRuleAntecedent* LLMMLL = new FuzzyRuleAntecedent();
    LLMMLL->joinWithAND(left_low_low_med, right_med_low_low);
    FuzzyRule* fr4 = new FuzzyRule(4, LLMMLL, drive_center);
    fuzzy->addFuzzyRule(fr4);

    FuzzyRuleAntecedent* LMMMML = new FuzzyRuleAntecedent();
    LMMMML->joinWithAND(left_low_med_med, right_med_med_low);
    FuzzyRule* fr5 = new FuzzyRule(5, LMMMML, drive_center);
    fuzzy->addFuzzyRule(fr5);

    FuzzyRuleAntecedent* LHHLLL = new FuzzyRuleAntecedent();
    LHHLLL->joinWithAND(left_low_high_high, right_low_low_low);
    FuzzyRule* fr6 = new FuzzyRule(6, LHHLLL, drive_small_left);
    fuzzy->addFuzzyRule(fr6);

    FuzzyRuleAntecedent* LHHMLL = new FuzzyRuleAntecedent();
    LHHMLL->joinWithAND(left_low_high_high, right_med_low_low);
    FuzzyRule* fr7 = new FuzzyRule(6, LHHMLL, drive_small_left);
    fuzzy->addFuzzyRule(fr7);

    FuzzyRuleAntecedent* LHHMML = new FuzzyRuleAntecedent();
    LHHMML->joinWithAND(left_low_high_high, right_med_med_low);
    FuzzyRule* fr8 = new FuzzyRule(8, LHHMML, drive_small_left);
    fuzzy->addFuzzyRule(fr8);

    FuzzyRuleAntecedent* LMHMML = new FuzzyRuleAntecedent();
    MHMM->joinWithAND(left_low_med_high, right_med_med_low);
    FuzzyRule* fr9 = new FuzzyRule(9, LMHMML, drive_small_left);
    fuzzy->addFuzzyRule(fr9);

    FuzzyRuleAntecedent* MHML = new FuzzyRuleAntecedent();
    MHML->joinWithAND(leftlm_med_high, rightmr_med_low);
    FuzzyRule* fr10 = new FuzzyRule(10, MHML, drive_small_left);
    fuzzy->addFuzzyRule(fr10);

    FuzzyRuleAntecedent* LMHLLL = new FuzzyRuleAntecedent();
    MHLL->joinWithAND(left_low_med_high, right_low_low_low);
    FuzzyRule* fr11 = new FuzzyRule(11, LMHLLL, drive_small_left);
    fuzzy->addFuzzyRule(fr11);

    FuzzyRuleAntecedent* LMMMLL = new FuzzyRuleAntecedent();
    LMMMLL->joinWithAND(left_low_med_med, right_med_low_low);
    FuzzyRule* fr12 = new FuzzyRule(12, LMMMLL, drive_small_left);
    fuzzy->addFuzzyRule(fr12);

    FuzzyRuleAntecedent* LMMLLL = new FuzzyRuleAntecedent();
    LMMLLL->joinWithAND(left_low_med_med, right_low_low_low);
    FuzzyRule* fr13 = new FuzzyRule(13, LMMLLL, drive_small_left);
    fuzzy->addFuzzyRule(fr13);

    FuzzyRuleAntecedent* LHMLLL = new FuzzyRuleAntecedent();
    LHMLLL->joinWithAND(left_low_high_med, right_low_low_low);
    FuzzyRule* fr14 = new FuzzyRule(14, LHMLLL, drive_small_left);
    fuzzy->addFuzzyRule(fr14);

    FuzzyRuleAntecedent* LMLLLL = new FuzzyRuleAntecedent();
    LMLLLL->joinWithAND(left_low_med_low, right_low_low_low);
    FuzzyRule* fr15 = new FuzzyRule(15, LMLLLL, drive_small_left);
    fuzzy->addFuzzyRule(fr15);

    FuzzyRuleAntecedent* LHLLLL = new FuzzyRuleAntecedent();
    LHLLLL->joinWithAND(left_low_high_low, right_low_low_low);
    FuzzyRule* fr16 = new FuzzyRule(16, LHLLLL, drive_full_left);
    fuzzy->addFuzzyRule(fr16);

    FuzzyRuleAntecedent* LLLLHL = new FuzzyRuleAntecedent();
    LLLLHL->joinWithAND(left_low_low_low, right_low_high_low);
    FuzzyRule* fr17 = new FuzzyRule(17, LLLLHL, drive_full_right);
    fuzzy->addFuzzyRule(fr17);

    FuzzyRuleAntecedent* LLLHHL = new FuzzyRuleAntecedent();
    LLLHHL->joinWithAND(left_low_low_low, right_high_high_low);
    FuzzyRule* fr18 = new FuzzyRule(18, LLLHHL, drive_small_right);
    fuzzy->addFuzzyRule(fr18);

    FuzzyRuleAntecedent* LLMHHL = new FuzzyRuleAntecedent();
    LLMHHL->joinWithAND(left_low_low_med, right_high_high_low);
    FuzzyRule* fr19 = new FuzzyRule(19, LLMHHL, drive_small_right);
    fuzzy->addFuzzyRule(fr19);

    FuzzyRuleAntecedent* LMMHHL = new FuzzyRuleAntecedent();
    LMMHHL->joinWithAND(left_low_med_med, right_high_high_low);
    FuzzyRule* fr20 = new FuzzyRule(20, LMMHHL, drive_small_right);
    fuzzy->addFuzzyRule(fr20);

    FuzzyRuleAntecedent* LMMHML = new FuzzyRuleAntecedent();
    LMMHML->joinWithAND(left_low_med_med, right_high_med_low);
    FuzzyRule* fr21 = new FuzzyRule(21, LMMHML, drive_small_right);
    fuzzy->addFuzzyRule(fr21);

    FuzzyRuleAntecedent* LLMHML = new FuzzyRuleAntecedent();
    LLMHML->joinWithAND(left_low_low_med, right_high_med_low);
    FuzzyRule* fr22 = new FuzzyRule(22, LLMHML, drive_small_right);
    fuzzy->addFuzzyRule(fr22);

    FuzzyRuleAntecedent* LLLHML = new FuzzyRuleAntecedent();
    LLLHML->joinWithAND(left_low_low_low, right_high_med_low);
    FuzzyRule* fr23 = new FuzzyRule(23, LLLHML, drive_small_right);
    fuzzy->addFuzzyRule(fr23);

    FuzzyRuleAntecedent* LLMMML = new FuzzyRuleAntecedent();
    LLMMML->joinWithAND(left_low_low_med, right_med_med_low);
    FuzzyRule* fr24 = new FuzzyRule(24, LLMMML, drive_small_right);
    fuzzy->addFuzzyRule(fr24);

    FuzzyRuleAntecedent* LLLMML = new FuzzyRuleAntecedent();
    LLLMML->joinWithAND(left_low_low_low, right_med_med_low);
    FuzzyRule* fr25 = new FuzzyRule(25, LLLMML, drive_small_right);
    fuzzy->addFuzzyRule(fr25);

    FuzzyRuleAntecedent* LLLMHL = new FuzzyRuleAntecedent();
    LLLMHL->joinWithAND(left_low_low_low, right_med_high_low);
    FuzzyRule* fr26 = new FuzzyRule(26, LLLMHL, drive_small_right);
    fuzzy->addFuzzyRule(fr26);

    FuzzyRuleAntecedent* LLLLML = new FuzzyRuleAntecedent();
    LLLLML->joinWithAND(left_low_low_low, right_low_med_low);
    FuzzyRule* fr27 = new FuzzyRule(27, LLLLML, drive_small_right);
    fuzzy->addFuzzyRule(fr27);

    FuzzyRuleAntecedent* LLLLLL = new FuzzyRuleAntecedent();
    LLLLLL->joinWithAND(left_low_low_low, right_low_low_low);
    FuzzyRule* fr28 = new FuzzyRule(28, LLLLLL, drive_center);	// should it be search?
    fuzzy->addFuzzyRule(fr28);

    // Revisions
    FuzzyRuleAntecedent* LLHLLL = new FuzzyRuleAntecedent();
    LLHLLL->joinWithAND(left_low_low_high, right_low_low_low);
    FuzzyRule* fr29 = new FuzzyRule(29, LHLL, drive_small_left);
    fuzzy->addFuzzyRule(fr29);

    FuzzyRuleAntecedent* LLMLLL = new FuzzyRuleAntecedent();
    LLMLLL->joinWithAND(left_low_low_med, right_low_low_low);
    FuzzyRule* fr30 = new FuzzyRule(30, LLMLLL, drive_small_left);
    fuzzy->addFuzzyRule(fr30);

    FuzzyRuleAntecedent* LLLMLL = new FuzzyRuleAntecedent();
    LLLMLL->joinWithAND(left_low_low_low, right_med_low_low);
    FuzzyRule* fr31 = new FuzzyRule(31, LLLMLL, drive_small_right);
    fuzzy->addFuzzyRule(fr31);

    FuzzyRuleAntecedent* LLLHLL = new FuzzyRuleAntecedent();
    LLLHLL->joinWithAND(left_low_low_low, right_high_low_low);
    FuzzyRule* fr32 = new FuzzyRule(32, LLLHLL, drive_small_right);
    fuzzy->addFuzzyRule(fr32);

    //New rules
    FuzzyRuleAntecedent* HLLLLL = new FuzzyRuleAntecedent();
    HLLLLL->joinWithAND(left_high_low_low, right_low_low_low);
    FuzzyRule* fr33 = new FuzzyRule(33, HLLLLL, drive_point_turn_left);
    fuzzy->addFuzzyRule(fr33);

    FuzzyRuleAntecedent* MMLLLL = new FuzzyRuleAntecedent();
    MMLLLL->joinWithAND(left_med_med_low, right_low_low_low);
    FuzzyRule* fr34 = new FuzzyRule(34, MMLLLL, drive_full_left);
    fuzzy->addFuzzyRule(fr34);

    FuzzyRuleAntecedent* MHLLLL = new FuzzyRuleAntecedent();
    MHLLLL->joinWithAND(left_med_high_low, right_low_low_low);
    FuzzyRule* fr35 = new FuzzyRule(35, MHLLLL, drive_full_left);
    fuzzy->addFuzzyRule(fr35);

    FuzzyRuleAntecedent* MMMLLL = new FuzzyRuleAntecedent();
    MMMLLL->joinWithAND(left_med_med_med, right_low_low_low);
    FuzzyRule* fr36 = new FuzzyRule(36, MMMLLL, drive_small_left);
    fuzzy->addFuzzyRule(fr36);

    FuzzyRuleAntecedent* MLLLLL = new FuzzyRuleAntecedent();
    MLLLLL->joinWithAND(left_med_low_low, right_low_low_low);
    FuzzyRule* fr37 = new FuzzyRule(37, MLLLLL, drive_point_turn_left);
    fuzzy->addFuzzyRule(fr37);

    FuzzyRuleAntecedent* LLLLLH = new FuzzyRuleAntecedent();
    LLLLLH->joinWithAND(left_low_low_low, right_low_low_high);
    FuzzyRule* fr38 = new FuzzyRule(38, LLLLLH, drive_point_turn_right);
    fuzzy->addFuzzyRule(fr38);

    FuzzyRuleAntecedent* LLLLMM = new FuzzyRuleAntecedent();
    LLLLMM->joinWithAND(left_low_low_low, right_low_med_med);
    FuzzyRule* fr39 = new FuzzyRule(39, LLLLMM, drive_full_right);
    fuzzy->addFuzzyRule(fr39);

    FuzzyRuleAntecedent* LLLLHM = new FuzzyRuleAntecedent();
    LLLLHM->joinWithAND(left_low_low_low, right_low_high_med);
    FuzzyRule* fr40 = new FuzzyRule(40, LLLLHM, drive_full_right);
    fuzzy->addFuzzyRule(fr40);

    FuzzyRuleAntecedent* LLLMMM = new FuzzyRuleAntecedent();
    LLLMMM->joinWithAND(left_low_low_low, right_med_med_med);
    FuzzyRule* fr41 = new FuzzyRule(41, LLLMMM, drive_small_right);
    fuzzy->addFuzzyRule(fr41);

    FuzzyRuleAntecedent* LLLLLM = new FuzzyRuleAntecedent();
    LLLLLM->joinWithAND(left_low_low_low, right_low_low_med);
    FuzzyRule* fr42 = new FuzzyRule(42, LLLLLM, drive_point_turn_right);
    fuzzy->addFuzzyRule(fr42);

    FuzzyRuleAntecedent* MMHHLL = new FuzzyRuleAntecedent();
    MMHHLL->joinWithAND(left_med_med_high, right_high_low_low);
    FuzzyRule* fr43 = new FuzzyRule(43, MMHHLL, drive_small_left);
    fuzzy->addFuzzyRule(fr43);

    FuzzyRuleAntecedent* MHHMLL = new FuzzyRuleAntecedent();
    MHHMLL->joinWithAND(left_med_high_high, right_med_low_low);
    FuzzyRule* fr44 = new FuzzyRule(44, MHHMLL, drive_small_left);
    fuzzy->addFuzzyRule(fr44);

    FuzzyRuleAntecedent* MMHHML = new FuzzyRuleAntecedent();
    MMHHML->joinWithAND(left_med_med_high, right_high_med_low);
    FuzzyRule* fr45 = new FuzzyRule(45, MMHHML, drive_small_left);
    fuzzy->addFuzzyRule(fr45);

    FuzzyRuleAntecedent* MHHMML = new FuzzyRuleAntecedent();
    MHHMML->joinWithAND(left_med_high_high, right_med_med_low);
    FuzzyRule* fr46 = new FuzzyRule(46, MHHMML, drive_small_left);
    fuzzy->addFuzzyRule(fr46);

    FuzzyRuleAntecedent* LMMHHM = new FuzzyRuleAntecedent();
    LMMHHM->joinWithAND(left_low_med_med, right_high_high_med);
    FuzzyRule* fr47 = new FuzzyRule(47, LMMHHM, drive_small_right);
    fuzzy->addFuzzyRule(fr47);

    FuzzyRuleAntecedent* LMHHMM = new FuzzyRuleAntecedent();
    LMMHHM->joinWithAND(left_low_med_high, right_high_med_med);
    FuzzyRule* fr48 = new FuzzyRule(48, LMHHMM, drive_small_right);
    fuzzy->addFuzzyRule(fr48);

    FuzzyRuleAntecedent* LLMHHM = new FuzzyRuleAntecedent();
    LLMHHM->joinWithAND(left_low_low_med, right_high_high_med);
    FuzzyRule* fr49 = new FuzzyRule(49, LLMHHM, drive_small_right);
    fuzzy->addFuzzyRule(fr49);

    FuzzyRuleAntecedent* LLHHMM = new FuzzyRuleAntecedent();
    LLHHMM->joinWithAND(left_low_low_high, right_high_med_med);
    FuzzyRule* fr50 = new FuzzyRule(50, LLHHHM, drive_small_right);
    fuzzy->addFuzzyRule(fr50);

    FuzzyRuleAntecedent* MMHHMM = new FuzzyRuleAntecedent();
    MMHHMM->joinWithAND(left_med_med_high, right_high_med_med);
    FuzzyRule* fr51 = new FuzzyRule(51, MMHHMM, drive_center);
    fuzzy->addFuzzyRule(fr51);
}

//Check is the other robot is close using the ToF sensors
void getToF() {
    RR_distance = sensor0.readRangeContinuousMillimeters();
    RM_distance = sensor1.readRangeContinuousMillimeters();
    LM_distance = sensor2.readRangeContinuousMillimeters();
    LL_distance = sensor3.readRangeContinuousMillimeters();
    // if (sensor0.timeoutOccurred() || sensor1.timeoutOccurred() || sensor2.timeoutOccurred() || sensor3.timeoutOccurred()) { Serial.print(" SENSOR TIMEOUT"); }
}

//Use the set up fuzzy settings to determine how to move
//Add 2 additional inputs
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

//Check the switch
void checkSwitch() {
    if(RSflag == LOW) {
        stop();
        // Serial.print("STOPPED");
        while(true);
    }
}

//Check to see if the robot is near a line and adjust movement accordingly
void checkLine() {
    if (!FLflag || !FRflag || prevFlagSet) {				// if front line triggered
        if (!prevFlagSet) {					// and if this is the FIRST detection of the line
            RGB.color(255, 255, 255);
            prevFlag = cur;					// reset the turn timer
            prevFlagSet = true;				// ensures timer is reset only ONCE
            moveState(1);						// stop before you fall off
        }
        moveState(10);						// begin/continue the turn sequence
    } else if ((!BRflag || !BLflag) && !prevFlagSet) {		// if back line triggered, move forward
        RGB.color(255, 255, 255);
        moveState(0);

        // prevFlagSet = true;

    } else if(!prevFlagSet) {  // if a line hasn't been seen, continue fuzzy
        // Serial.println("Doing Fuzzy");
        // prevFlagSet = false;
    }
}
