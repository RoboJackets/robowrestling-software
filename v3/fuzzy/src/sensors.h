//
// Created by Logan Schick on 8/31/2018.
//

#ifndef MAIN_CPP_SENSORS_H
#define MAIN_CPP_SENSORS_H

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
boolean start = true;

// Remote switch module
int RS = D4;
boolean RSflag = false;

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

#endif //MAIN_CPP_SENSORS_H
