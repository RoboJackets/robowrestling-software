#include "diagnostic.h"

#include <string>

void setup_radio() {
    RFM69 radio;
    radio.initialize(FREQUENCY, MYNODEID, NETWORKID);
    radio.setHighPower();
}

void send_data(byte[] input) {

    static char sendbuffer[62];
    static int sendlength = 0;

    if (Serial.available() > 0)
  {
    
    if (input != '\r') // not a carriage return
    {
      sendbuffer[sendlength] = input[i];
      sendlength++;
    }

    // If the input is a carriage return, or the buffer is full:
    
    if ((input == '\r') || (sendlength == 61)) // CR or buffer full
    {
      // Send the packet
      
    radio.sendWithRetry(TONODEID, sendbuffer, sendlength);
    sendlength = 0;
    }
  }
}

void recieve_data() {
    if (radio.receiveDone())
  {
    radio.sendACK();
  }
  //run a test
  if (radio.DATA[0] = 0){
      check_motor();
  } else if (radio.DATA[0] = 1) {
      check_line_sensor();
  } else {
      check_lidar();
}

void check_motor() {
    drive(127,255);
    delay(1000);
    drive(0,0);
    drive(63,191);
    delay(1000);
    drive(0,0);
}

void check_line_sensor() {
	left_line_hit = !digitalReadFast(LEFT_INT_LINE);
    right_line_hit = !digitalReadFast(RIGHT_INT_LINE);
}

void check_accel() {
    imu.readSensor();
    Serial.println("Accel_X: " + imu.getAccelX_mss());
    Serial.println("Accel_Y: " + imu.getAccelY_mss());
}

void check_gyro() {
    imu.readSensor();
    Serial.println("Gyro_Z: " + imu.getGyroZ_rads());
}

void check_lidar() {
    digitalWrite(LIDAR12_MUX, LOW);
    read_lidar(LIDAR12_SERIAL);
    digitalWrite(LIDAR12_MUX, HIGH);
    read_lidar(LIDAR12_SERIAL);
    digitalWrite(LIDAR34_MUX, LOW);
    read_lidar(LIDAR34_SERIAL);
    digitalWrite(LIDAR34_MUX, HIGH);
    read_lidar(LIDAR34_SERIAL);
    digitalWrite(LIDAR56_MUX, LOW);
    read_lidar(LIDAR56_SERIAL);
    digitalWrite(LIDAR56_MUX, HIGH);
    read_lidar(LIDAR56_SERIAL);
}

void read_lidar(auto LIDAR) {
    byte byteArray [9];
    Serial.println(LIDAR);
    if (LIDAR) {
        LIDAR.readBytes(byteArray, 9); // write output of read to an array of length 9
        Serial.println("Distance: " + (byteArray[3] << 8) | (byteArray[2] << 0));
        Serial.println("Strength: " + (byteArray[5] << 8) | (byteArray[4] << 0));
    }
}
// Byte0 Byte 1 Byte2 Byte3  Byte4      Byte5      Byte6  Byte7  Byte8
// 0x89  0x89 Dist_L  Dist_H Strength_L Strength_H Temp_L Temp_H Checksum
// byte2 is distance, overflows into byte3