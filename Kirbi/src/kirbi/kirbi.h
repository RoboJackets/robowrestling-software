#include "Arduino.h"

enum States;

/* IMU and distance sensor data buffers */
double x_accel[25];
double y_accel[25];
int distances_right[50];
int distances_left[50];

/* set motor speed */
void drive(int left, int right);

/* state machine */
State state_machine(State last_state);

/* interrupt methods */
void do_line_action_left();
void do_line_action_right();
void do_startup_action();

/* 
sensor read methods 
void update buffers with new data
 */
void get_accel();
void get_gyro();
void get_distances();
void get_current();


