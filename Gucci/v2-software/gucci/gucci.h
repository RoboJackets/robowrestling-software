
#ifndef gucci_h
#define gucci_h

#include "Arduino.h"
#include <Wire.h>
//#include "CircularArray.h" //?
#include "ICM20948.h"
#include "VL53L0X.h"
#include "math.h"


#define ESC_L_SERIAL Serial1
#define ESC_L_RX 22
#define ESC_L_TX 26
#define ESC_R_SERIAL Serial3
#define ESC_R_RX 7
#define ESC_R_TX 8
#define ESC_ADDRESS 128

#define MAX_DIST 1500 //Max distance we care about
#define CLOSE_DIST 500

#define LEFT_A_ENCODER 38
#define RIGHT_A_ENCODER 22
#define LEFT_B_ENCODER 37
#define RIGHT_B_ENCODER 21

#define LEFT_CURRENT A21
#define RIGHT_CURRENT A0

#define IMU_ADDRESS_PIN 9
#define IMU_SDA 8
#define IMU_SCL 7

#define TOF_L 0
#define TOF_L_45 1
#define TOF_L_C 2
#define TOF_R_C 30
#define TOF_R_45 31
#define TOF_R 32

#define RIGHT_REF_LINE 35
#define LEFT_REF_LINE 23
#define RIGHT_INT_LINE 19
#define LEFT_INT_LINE 18

#define RIGHT_THRES_LINE 150
#define LEFT_THRES_LINE 150

#define LINE_COOLDOWN 100

#define REMOTE_PIN 17

#define DIST_LEFT_SIDE    dist[0]
#define DIST_LEFT_CORNER  dist[1]
#define DIST_LEFT_CENTER  dist[2]
#define DIST_RIGHT_CENTER dist[3]
#define DIST_RIGHT_CORNER dist[4]
#define DIST_RIGHT_SIDE   dist[5]



enum State {
    SEARCH_LEFT,
    SEARCH_RIGHT,
    ADJUST_1_LEFT,
    ADJUST_1_RIGHT,
    ADJUST_2_LEFT,
    ADJUST_2_RIGHT,
    ADJUST_3_LEFT,
    ADJUST_3_RIGHT,
    ADJUST_4_LEFT,
    ADJUST_4_RIGHT,
    SLAMMY_WHAMMY,
    MEGA_SLAMMY_WHAMMY,
    PANIC_HIT,
    PANIC_FIRE,
    WAIT_FOR_START,
    STARTUP
};

enum Location{
	FRONT_FAR,
	FRONT_CLOSE,
	LEFT_CORNER_FRONT,
	RIGHT_CORNER_FRONT,
	LEFT_CORNER,
	RIGHT_CORNER.
	LEFT_CORNER_SIDE,
	RIGHT_CORNER_SIDE,
	LEFT_SIDE,
	RIGHT_SIDE
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
void left_on_line_int();
void right_on_line_int();
void left_off_line_int();
void right_off_line_int();
void do_startup_action();
void increment_encoder_left();
void increment_encoder_right();

/* setup methods */

void setup_imu();
void setup_distance();
void setup_current();
void setup_motors();
void setup_encoders();
void setup_line();
void setup_remote();

/**
sensor read methods
void update buffers with new data
 */
void get_accel();
void get_gyro();
void get_distances();
void get_current();

Location get_opponent();
/*
other
*/
void balance_motors();


#endif
