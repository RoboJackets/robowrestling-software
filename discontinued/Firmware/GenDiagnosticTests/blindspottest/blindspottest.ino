#define TOF_L 0
#define TOF_L_45 1
#define TOF_L_C 2
#define TOF_R_C 30
#define TOF_R_45 31
#define TOF_R 32

#define LEFT_LIDAR_SERIAL Serial4
#define RIGHT_LIDAR_SERIAL Serial1
#define LEFT_LIDAR 4 // for use in read lidar methods
#define RIGHT_LIDAR 1

int dist[6];
#include <Wire.h>

int not_visible_count = 0;
int loop_count = 0;
int sensor_index = 5;
int num_iterations = 250;

#define DIST_L 30
#define DIST_L_45 28
#define DIST_R 2
#define DIST_R_45 3

#define MAX_DIST 150

byte factoryReset[4] = {0x5A, 0x04, 0x10, 0x6E};
byte saveSettings[4] = {0x5A, 0x04, 0x11, 0x6F};
byte setFramerate[6] = {0x5A, 0x06, 0x03, 0x00, 0xF0, 0xD3}; //index 3 and 4 set the frame rate to 1000/x where x is 0x[4][3]
byte setBaudrate[8] = {0x5A, 0x08, 0x06,0x00, 0x50, 0x46, 0x00,0x8A}; //To change the baud you must set the baud to the current baud to communicate, write the baud and save settings, 
                                                                      //then close and reopen at the new baud. Out of box baud is 115200 for tfmini
int tim = 0;
int lasttim = 0;
void setup() {
  // put your setup code here, to run once:
    Serial.println(1);
    LEFT_LIDAR_SERIAL.setRX(31);
    LEFT_LIDAR_SERIAL.setTX(32);
    while(!LEFT_LIDAR_SERIAL){delay(10);}
//    LEFT_LIDAR_SERIAL.begin(115200);
//    LEFT_LIDAR_SERIAL.write(factoryReset, 4);
    
    LEFT_LIDAR_SERIAL.begin(4608000);
    LEFT_LIDAR_SERIAL.write(setBaudrate, 8);
    LEFT_LIDAR_SERIAL.write(saveSettings, 4);
    LEFT_LIDAR_SERIAL.end();
    LEFT_LIDAR_SERIAL.begin(2000000);
    LEFT_LIDAR_SERIAL.write(setFramerate, 6);
    LEFT_LIDAR_SERIAL.write(saveSettings, 4);
    
    
    RIGHT_LIDAR_SERIAL.setRX(0);
    RIGHT_LIDAR_SERIAL.setTX(1);
    while(!RIGHT_LIDAR_SERIAL){delay(10);}
//    RIGHT_LIDAR_SERIAL.begin(115200);
//    RIGHT_LIDAR_SERIAL.write(factoryReset, 4);

    RIGHT_LIDAR_SERIAL.begin(4608000);
    RIGHT_LIDAR_SERIAL.write(setBaudrate, 8);
    RIGHT_LIDAR_SERIAL.write(saveSettings, 4);
    RIGHT_LIDAR_SERIAL.end();
    RIGHT_LIDAR_SERIAL.begin(2000000);
    RIGHT_LIDAR_SERIAL.write(setFramerate, 6);
    RIGHT_LIDAR_SERIAL.write(saveSettings, 4);
    
    Serial.println(2);
    pinMode(DIST_L, INPUT);
    pinMode(DIST_L_45, INPUT);
    pinMode(DIST_R, INPUT);
    pinMode(DIST_R_45, INPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
    dist[0] = digitalRead(DIST_L);
    dist[1] = digitalRead(DIST_L_45);
    dist[2] = digitalRead(DIST_R);
    dist[3] = digitalRead(DIST_R_45);
    dist[4] = read_lidar(LEFT_LIDAR);
    dist[5] = read_lidar(RIGHT_LIDAR);
//    Serial.print(dist[0]);
//    Serial.print(dist[1]);
//    Serial.print(dist[2]);
//    Serial.print(dist[3]);
//      Serial.println(dist[4]);
//      Serial.println(dist[5]);
//    Serial.println();
    if (dist[sensor_index] >= MAX_DIST) {
//      Serial.println(dist[sensor_index]);
      not_visible_count+=1;
    }
    loop_count += 1;
    if (loop_count == num_iterations) {
      tim = micros() - lasttim;
      lasttim = micros();
      Serial.println(String(not_visible_count / (double) num_iterations * 100) + "% missed. Time since last " + tim);
      loop_count = 0;
      not_visible_count = 0;
    } 
    
//    for (int i = sizeof(dist)/sizeof(dist[0])-1; i >= 0; i--) {
//      Serial.print(dist[i]);
//      Serial.print(" ");
//      if (dist[i] > 0 && dist[i] < 1250) {
//        yes = true;
//      }
//    }
//    Serial.println();
//    if (yes) {
//      Serial.println("yes");
//    } else {
//      Serial.println("no");
//    }
//    delay(100);
}

int read_lidar(int serial_port) {
    byte bytes[9];
    if (serial_port == 4) {
      LEFT_LIDAR_SERIAL.readBytes(bytes, 9);
    } else {
      RIGHT_LIDAR_SERIAL.readBytes(bytes, 9);
    }
//    Serial.println(String(bytes[0]) + " " + String(bytes[1]) + " " + String(bytes[2]) + " " + String(bytes[3]) + " " + String(bytes[4]) + " " + String(bytes[5]) + " " + String(bytes[6]) + " " + String(bytes[7]) + " " + String(bytes[8]));
    int dist_low = 0;
    int value = -1;
    while (dist_low < 9 && value == -1) {
        if (bytes[dist_low] == 0x59) {
            if (dist_low == 0) {
                if (bytes[8] == 0x59) {
                    value = bytes[1] + (bytes[2] << 8);
                } else if (bytes[1] == 0x59) {
                    value = bytes[2] + (bytes[3] << 8);
                }
            } else if (dist_low == 7) {
                if (bytes[8] == 0x59) {
                    value = bytes[0] + (bytes[1] << 8);
                }
            } else {
                if (bytes[++dist_low] == 0x59) {
                    value = bytes[++dist_low] + ((bytes[++dist_low]) << 8);
                }
            }
        }
        dist_low++;
//    Serial.println(value);
    }
    if (value == 0 || value == -1) {
        return MAX_DIST+1;
    }
    delay(1);
    return value;
}
