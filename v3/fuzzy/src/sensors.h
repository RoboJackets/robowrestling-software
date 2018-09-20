//
// Created by Logan Schick on 8/31/2018.
//

#include <VL53L0X.h>

#include <Fuzzy.h>

#ifndef MAIN_CPP_SENSORS_H
#define MAIN_CPP_SENSORS_H

// Time of Flight sensors
extern VL53L0X sensor0;	// RR
extern VL53L0X sensor1;	// RM
extern VL53L0X sensor2;	// LM
extern VL53L0X sensor3;	// LL
extern uint16_t LL_distance;
extern uint16_t LM_distance;
extern uint16_t RM_distance;
extern uint16_t RR_distance;

// Line sensors
extern int FL;    // AUX BOARD SWITCHED FL and FR up
extern int FR;    // A5 does not support attachInterrupt, so jump A5 to D7 on the board, also cut INT line
extern int BL;
extern int BR;
extern boolean FLflag; // active low
extern boolean FRflag;
extern boolean BLflag;
extern boolean BRflag;
extern int cur;
extern int prevFlag;
// boolean moving;
extern boolean prevFlagSet;
extern boolean start;

// Remote switch module
extern int RS;
extern boolean RSflag;

// Car ESCs
extern Servo LESC;
extern Servo RESC;
extern int Lmotor;
extern int Rmotor;
extern int L_command;
extern int R_command;
extern int L_dir;
extern int R_dir;

// Fuzzy logic
extern Fuzzy* fuzzy;
extern float output;
extern String decision;

#endif //MAIN_CPP_SENSORS_H
