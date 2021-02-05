#ifndef gucci_h
#define gucci_h

#include "Arduino.h"
#include "math.h"


#define LIDAR12_SERIAL Serial3 //Test which is what direction
#define LIDAR12_RX 7
#define LIDAR12_TX 8
#define LIDAR12_MUX 2
#define LIDAR34_SERIAL Serial1
#define LIDAR34_RX 0
#define LIDAR34_TX 1
#define LIDAR34_MUX 28
#define LIDAR56_SERIAL Serial2
#define LIDAR56_RX 9
#define LIDAR56_TX 10
#define LIDAR56_MUX 25

#define ESC_L_SERIAL Serial4 //Verify This is the Left Motor
#define ESC_L_RX 31
#define ESC_L_TX 32
#define ESC_R_SERIAL Serial5
#define ESC_R_RX 34
#define ESC_R_TX 33
#define ESC_ADDRESS 128 //Verify this address

#define MAX_DIST 1500 //Max distance we care about
#define CLOSE_DIST 500

#define IMU_SDA 4
#define IMU_SCL 3

#define LEFT_INT_LINE 15
#define RIGHT_INT_LINE 16
#define LINE_REF A22
#define THRES_LINE 190
#define LINE_COOLDOWN 100

#define REMOTE_PIN 14

#define RADIO_MOSI 11
#define RADIO_MISO 12
#define RADIO_SCK 13
#define RADIO_DIO 22
#define RADIO_RESET 29
#define RADIO_NSS 30

#define NEO_DI 6

#define DIST_LEFT_SIDE    dist[0]
#define DIST_LEFT_CORNER  dist[1]
#define DIST_LEFT_CENTER  dist[2]
#define DIST_RIGHT_CENTER dist[3]
#define DIST_RIGHT_CORNER dist[4]
#define DIST_RIGHT_SIDE   dist[5]


/* set motor speed */
void drive(int left, int right);

/* interrupt methods */
void left_line_int();
void right_line_int();
void do_startup_action();

/* setup methods */
void setup_imu();
void setup_distance();
void setup_motors();
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

#endif