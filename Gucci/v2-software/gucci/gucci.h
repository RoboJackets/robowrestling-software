
#ifndef gucci_h
#define gucci_h

#include "Arduino.h"
#include <Wire.h>
//#include "CircularArray.h" //?
#include "ICM20948.h"
#include "VL53L0X.h"
#include "math.h"

#define LL_INT 18
#define RL_INT 19
#define LINE_COOLDOWN 100

#define ESC_L_SERIAL Serial1
#define ESC_R_SERIAL Serial3
#define ESC_ADDRESS 128

#define MAX_DIST 1500 //Max distance we care about

#define LEFT_ENCODER 38
#define RIGHT_ENCODER 22

#define LEFT_CURRENT A21
#define RIGHT_CURRENT A0

enum State {
    SEARCH_LEFT,
    SEARCH_RIGHT,
    ADJUST_LEFT,
    ADJUST_RIGHT,
    SLAMMY_WHAMMY,
    PANIC_HIT,
    PANIC_FIRE,
    WAIT_FOR_START,
    STARTUP
};

/* IMU and distance sensor data buffers */
//CircularArray<double> x_accel;
//CircularArray<double> y_accel;
//CircularArray<int[6]> distances;

/* set motor speed */
void drive(int left, int right, bool left_reverse, bool right_reverse);

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
