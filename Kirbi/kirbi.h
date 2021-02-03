
#ifndef kirbi_h
#define kirbi_h

#include "Arduino.h"
#include "math.h"

#define LIDAR4_SERIAL Serial4
#define LIDAR3_SERIAL Serial1
#define LIDAR12_SERIAL Serial3
#define LIDAR56_SERIAL Serial2
#define LIDAR_4 4
#define LIDAR_3 1
#define LIDAR_12 3
#define LIDAR_56 2

#define ESC_SERIAL Serial5
#define ESC_ADDRESS ((unsigned int) 128)
#define ESC_CHECKSUM ((unsigned int) 0b01111111)

#define MAX_DIST 150 //Whatever the lidar returns when it doesn't see anything
#define CLOSE_DIST 100

#define IMU_ADDRESS_PIN 9
#define IMU_SDA 8
#define IMU_SCL 7

#define LINE_REF A22
#define RIGHT_INT_LINE 23
#define LEFT_INT_LINE 35

#define RADIO_RESET 29
#define RADIO_NSS 30
#define RADIO_DIC0 22
#define RADIO_MOSI 11
#define RADIO_MISO 12

#define LED 6

#define LINE_THRES 190

#define REMOTE_PIN 17

#define DIST_LEFT_SIDE    dist[0]
#define DIST_LEFT_CORNER  dist[1]
#define DIST_LEFT_CENTER  dist[2]
#define DIST_RIGHT_CENTER dist[3]
#define DIST_RIGHT_CORNER dist[4]
#define DIST_RIGHT_SIDE   dist[5]

/* set motor speed */
void drive(int left, int right);

/* interrupt methods */
void left_on_line_int();
void right_on_line_int();
void left_off_line_int();
void right_off_line_int();
void do_startup_action();
/* setup methods */

void setup_imu();
void setup_distance();
void setup_current();
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
int read_lidar(int serial_port);
void get_current();



#endif
