
#ifndef gucci_h
#define gucci_h

#include "Arduino.h"
#include "CircularArray.h" //?
#include "ICM20948.h"
#include "VL53L0X.h"
#include "math.h"

// #define LEFT_LIDAR_SERIAL Serial1
// #define RIGHT_LIDAR_SERIAL Serial4

#define ESC_L_SERIAL Serial1
#define ESC_R_SERIAL Serial3
#define ESC_ADDRESS 128

#define MAX_DIST 150 //Max distance we care about

#define LEFT_ENCODER 38
#define RIGHT_ENCODER 22

#define LEFT_CURRENT A21
#define RIGHT_CURRENT A0

enum States;

/* IMU and distance sensor data buffers */
CircularArray<double> x_accel;
CircularArray<double> y_accel;
CircularArray<int[6]> distances;

/* distance sensors */
VL53L0X tof_left;
VL53L0X tof_left_45;
VL53L0X tof_left_center;
VL53L0X tof_right_center;
VL53L0X tof_right_45;
VL53L0X tof_right;

/* acceleration timing variables */
int curr_time;
int prev_time_accel;
int check_accel;

/* encoder counts */
int right_encoder;
int left_encoder;

double left_multi;
double right_multi;

double left_turn_ratio;
double right_turn_ratio;


/* Current sensing stuff */
double r1 = 2.3;
double r2 = 7.28;
double nominal_current = 4.12;
const double precalc = 2.01873 //nominal_current*(sqrt(r1/(r1+r2)))
const double tw = 42.2;
int total_currentxtime_left;
int total_currentxtime_right;
double percent_overloaded_left;
double percent_overloaded_right;
int prev_time_current; //for use with curr_time
int last_read_current;
int check_overload;
const double voltage_to_current = .01611328;


/* set motor speed */
void drive(int left, int right);

/* state machine */
State state_machine(State last_state);

/* interrupt methods */
void do_line_action_left();
void do_line_action_right();
void do_startup_action();
void increment_encoder_left();
void increment_encoder_right();

/* setup methods */

void setup_imu();
void setup_distance();
void setup_current();
void setup_motors();

/**
sensor read methods
void update buffers with new data
 */
void get_accel();
void get_gyro();
void get_distances();
void get_current();

/*
other
*/
void balance_motors();


#endif
