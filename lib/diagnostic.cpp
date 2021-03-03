#include "diagnostic.h"

void setup_radio() {
    radio.initialize(FREQUENCY, MYNODEID, NETWORKID);
    radio.setHighPower();
}

void send_data(byte input[]) {
    radio.sendWithRetry(TONODEID, input, sizeof(input)/sizeof(input[0]));
}


void recieve_data() {
    if (radio.receiveDone())
  {
    radio.sendACK();
  }
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
    byte readings;
	Serial.println(!digitalReadFast(LEFT_INT_LINE));
    Serial.println(!digitalReadFast(RIGHT_INT_LINE));
    reading = !digitalReadFast(LEFT_INT_LINE) << 1 | !digitalReadFast(RIGHT_INT_LINE) << 0;
    //return reading;
}

void check_accelX() {
    imu.readSensor(); 
    Serial.printf("Accel_X: %f\n", imu.getAccelX_mss());
    //return imu.getAccelX_mss();
}

void check_accelY() {
    imu.readSensor(); 
    Serial.printf("Accel_Y: %f\n", imu.getAccelY_mss());
    //return imu.getAccelY_mss();
}

void check_gyro() {
    imu.readSensor();
    Serial.printf("Gyro_Z: %f\n", imu.getGyroZ_rads());
    //return imu.GetgyroZ_rads();
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
    Serial.println(LIDAR);
    if (LIDAR) {
        LIDAR.readBytes(byteArray, 9); // write output of read to an array of length 9
        Serial.println("Distance: " + ((byteArray[3] << 8) | (byteArray[2] << 0)));
        Serial.println("Strength: " + ((byteArray[5] << 8) | (byteArray[4] << 0)));
    }
}
// Byte0 Byte 1 Byte2 Byte3  Byte4      Byte5      Byte6  Byte7  Byte8
// 0x89  0x89 Dist_L  Dist_H Strength_L Strength_H Temp_L Temp_H Checksum
// byte2 is distance, overflows into byte3