#include "lib/diagnostic.h"
#include "lib/diagnostic.cpp"
#include "Gucci/gucci.cpp"
#include "lib/ICM20948.cpp"

byte check = 11;

void setup()
{
    Serial.begin(9600);
    Serial.println("Starting Setup");
    setup_imu();
    Serial.println("Setup IMU");
    setup_distance();
    Serial.println("Setup Distance");
    setup_motors();
    Serial.println("Setup Motors");
    setup_line();
    Serial.println("Setup Line");
    setup_remote();
    Serial.println("Finished Setup");
    Serial.println("Codes: (0-6)-tfmini, 7-accel, 8-gyro, 9-motor, 10-line sensor");
}

void loop()
{
    recieve_data();
    check = radio.DATA[0];
    if(Serial.available() > 0) {
        check = Serial.read();
        Serial.println("Codes: (0-6)-tfmini, 7-accel, 8-gyro, 9-motor, 10-line sensor");
    }
    switch (check) {
        case 0:
            check_lidar();
            break;
        case 1: {
            digitalWrite(LIDAR12_MUX, LOW);
            Serial.println(LIDAR12_SERIAL);
            if (LIDAR12_SERIAL) {
                LIDAR12_SERIAL.readBytes(byteArray, 9); // write output of read to an array of length 9
                Serial.println("Distance: " + ((byteArray[3] << 8) | (byteArray[2] << 0)));
                Serial.println("Strength: " + ((byteArray[5] << 8) | (byteArray[4] << 0)));
            }
            //byte send[] = {byteArray[3], (byteArray[2], byteArray[5], byteArray[4]}
            //send_data(send);
            break;
        }
        case 2: {
            digitalWrite(LIDAR12_MUX, HIGH);
            Serial.println(LIDAR12_SERIAL);
            if (LIDAR12_SERIAL) {
                LIDAR12_SERIAL.readBytes(byteArray, 9); // write output of read to an array of length 9
                Serial.println("Distance: " + ((byteArray[3] << 8) | (byteArray[2] << 0)));
                Serial.println("Strength: " + ((byteArray[5] << 8) | (byteArray[4] << 0)));
            }
            //byte send[] = {byteArray[3], (byteArray[2], byteArray[5], byteArray[4]}
            //send_data(send);
            break;
            }
            
        case 3: {
            digitalWrite(LIDAR34_MUX, LOW);
            Serial.println(LIDAR34_SERIAL);
            if (LIDAR34_SERIAL) {
                LIDAR34_SERIAL.readBytes(byteArray, 9); // write output of read to an array of length 9
                Serial.println("Distance: " + ((byteArray[3] << 8) | (byteArray[2] << 0)));
                Serial.println("Strength: " + ((byteArray[5] << 8) | (byteArray[4] << 0)));
            }
            //byte send[] = {byteArray[3], (byteArray[2], byteArray[5], byteArray[4]}
            //send_data(send);
            break;
            }
            
        case 4: {
            digitalWrite(LIDAR34_MUX, HIGH);
            Serial.println(LIDAR34_SERIAL);
            if (LIDAR34_SERIAL) {
                LIDAR34_SERIAL.readBytes(byteArray, 9); // write output of read to an array of length 9
                Serial.println("Distance: " + ((byteArray[3] << 8) | (byteArray[2] << 0)));
                Serial.println("Strength: " + ((byteArray[5] << 8) | (byteArray[4] << 0)));
            }
            //byte send[] = {byteArray[3], (byteArray[2], byteArray[5], byteArray[4]}
            //send_data(send);
            break;
        }
            
        case 5: {
            digitalWrite(LIDAR56_MUX, LOW);
            Serial.println(LIDAR56_SERIAL);
            if (LIDAR56_SERIAL) {
                LIDAR56_SERIAL.readBytes(byteArray, 9); // write output of read to an array of length 9
                Serial.println("Distance: " + ((byteArray[3] << 8) | (byteArray[2] << 0)));
                Serial.println("Strength: " + ((byteArray[5] << 8) | (byteArray[4] << 0)));
            }
            //byte send[] = {byteArray[3], (byteArray[2], byteArray[5], byteArray[4]}
            //send_data(send);
            break;
        }
            
        case 6: {
            digitalWrite(LIDAR56_MUX, HIGH);
            Serial.println(LIDAR56_SERIAL);
            if (LIDAR56_SERIAL) {
                LIDAR56_SERIAL.readBytes(byteArray, 9); // write output of read to an array of length 9
                Serial.println("Distance: " + ((byteArray[3] << 8) | (byteArray[2] << 0)));
                Serial.println("Strength: " + ((byteArray[5] << 8) | (byteArray[4] << 0)));
            }
            //byte send[] = {byteArray[3], (byteArray[2], byteArray[5], byteArray[4]}
            //send_data(send);
            break;
        }
            
        case 7:
        {
            /*
            byte send[8];
            packet.val = check_accelX();
            for (int i = 0; i < 4; i++) {
                send[i] = packet.bytes[i];
            }
            packet.val = check_accelY();
            for (int i = 4; i < 8; i++) {
                send[i] = packet.bytes[i];
            }
            send_data(send);
            */
            check_accelX();
            check_accelY();
            break;
        }
        case 8:
            //packet.val = check_gyro();
            //send_data(packet.bytes);
            check_gyro();
            break;
        case 9:
            check_motor();
            break;
        case 10:
            //send_data(check_line_sensor());
            check_line_sensor();
            break;
        default:
            break;
    }
    
}
