
#ifndef kirbi_h
#define kirbi_h

#include "Arduino.h"
#include "CircularArray.h" //?
#include "ICM20948.h"
#include "math.h"

#define LEFT_LIDAR_SERIAL Serial4
#define RIGHT_LIDAR_SERIAL Serial1
#define LEFT_LIDAR 4 // for use in read lidar methods
#define RIGHT_LIDAR 1

#define ESC_SERIAL Serial5
#define ESC_ADDRESS ((unsigned int) 128)
#define ESC_CHECKSUM ((unsigned int) 0b01111111)

#define MAX_DIST 150 //Whatever the lidar returns when it doesn't see anything
#define CLOSE_DIST 100

/* Definitions for pin numbers or Omron sensors */
#define DIST_L 30
#define DIST_L_45 28
#define DIST_R 2
#define DIST_R_45 3

#define LEFT_A_ENCODER 38
#define RIGHT_A_ENCODER 22
#define LEFT_B_ENCODER 37
#define RIGHT_B_ENCODER 21

#define LEFT_CURRENT A21
#define RIGHT_CURRENT A0

#define IMU_ADDRESS_PIN 9
#define IMU_SDA 8
#define IMU_SCL 7

#define LINE_REF A22
#define RIGHT_INT_LINE 19
#define LEFT_INT_LINE 18

#define LINE_THRES 190

#define REMOTE_PIN 17

#define DIST_LEFT_SIDE    dist[0]
#define DIST_LEFT_CORNER  dist[1]
#define DIST_LEFT_CENTER  dist[2]
#define DIST_RIGHT_CENTER dist[3]
#define DIST_RIGHT_CORNER dist[4]
#define DIST_RIGHT_SIDE   dist[5]

enum State {
    SEARCH,
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
    PANIC_FIRE
};

enum Location{
    FRONT_FAR,
    FRONT_CLOSE,
    LEFT_CORNER_FRONT,
    RIGHT_CORNER_FRONT,
    LEFT_CORNER,
    RIGHT_CORNER,
    LEFT_CORNER_SIDE,
    RIGHT_CORNER_SIDE,
    LEFT_SIDE,
    RIGHT_SIDE,
    BEHIND
};

/* set motor speed */
void drive(int left, int right);

/* state machine */
State state_machine();

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
bool get_line_flag();
void get_accel();
void get_gyro();
void get_distances();
int read_lidar(int serial_port);
void get_current();
Location get_opponent();

/*
other
*/
void balance_motors();


#endif
