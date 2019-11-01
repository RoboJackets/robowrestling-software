
#ifndef kirbi_h
#define kirbi_h

#include "Arduino.h"
#include "ICM20948.h"

enum States;

/* IMU and distance sensor data buffers */
double x_accel[25];
int curr_x_accel;
double y_accel[25];
int curr_y_accel;
int distances_right[60];
int curr_dist_right;
int distances_left[60];
int curr_dist_left;
int current[10];
int currentcurrent;

int curr_time;
int prev_time;
int check_accel;

/* set motor speed */
void drive(int left, int right);

/* state machine */
State state_machine(State last_state);

/* interrupt methods */
void do_line_action_left();
void do_line_action_right();
void do_startup_action();

/* setup methods */

void setup_imu();
void setup_distance();
void setup_current();
void setup_motors();

/*
sensor read methods
void update buffers with new data
 */
void get_accel();
void get_gyro();
void get_distances();
void get_current();


#endif