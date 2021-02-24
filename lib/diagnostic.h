#ifndef diagnostic_h
#define diagnostic_h

//#include <RFM69.h>
//#include <SPI.h>
#include "../Gucci/gucci.h"

#define NETWORKID 0
#define MYNODEID 1
#define TONODEID 2
#define FREQUENCY RF69_915MHZ
#define USEACK true


void setup_radio();
void send_data();
void recieve_data();
void check_motor();
void check_line_sensor();
void check_accel();
void check_gyro();
void check_lidar();
void read_lidar(auto);

#endif