#include <strategy/diagnostic/diagnostic.h>

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
    Serial.println("Codes: (0-6)-tfmini, 7-accel, 8-gyro, 9-motor, 10-line sensor")
}

void loop()
{
    if(Serial.available() > 0) {
        check = Serial.read();
        Serial.println("Codes: (0-6)-tfmini, 7-accel, 8-gyro, 9-motor, 10-line sensor")
    }
    switch (check) {
        case 0:
            check_lidar();
            break;
        case 1:
            digitalWrite(LIDAR12_MUX, LOW);
            byte byteArray [9];
            Serial.println(LIDAR12_SERIAL);
            if (LIDAR12_SERIAL) {
                LIDAR.readBytes(byteArray, 9); // write output of read to an array of length 9
                Serial.println("Distance: " + (byteArray[3] << 8) | (byteArray[2] << 0));
                Serial.println("Strength: " + (byteArray[5] << 8) | (byteArray[4] << 0));
            }
            break;
        case 2:
            digitalWrite(LIDAR12_MUX, HIGH);
            byte byteArray [9];
            Serial.println(LIDAR12_SERIAL);
            if (LIDAR12_SERIAL) {
                LIDAR.readBytes(byteArray, 9); // write output of read to an array of length 9
                Serial.println("Distance: " + (byteArray[3] << 8) | (byteArray[2] << 0));
                Serial.println("Strength: " + (byteArray[5] << 8) | (byteArray[4] << 0));
            }
            break;
        case 3:
            digitalWrite(LIDAR34_MUX, LOW);
            byte byteArray [9];
            Serial.println(LIDAR34_SERIAL);
            if (LIDAR34_SERIAL) {
                LIDAR.readBytes(byteArray, 9); // write output of read to an array of length 9
                Serial.println("Distance: " + (byteArray[3] << 8) | (byteArray[2] << 0));
                Serial.println("Strength: " + (byteArray[5] << 8) | (byteArray[4] << 0));
            }
            break;
        case 4:
            digitalWrite(LIDAR12_MUX, HIGH);
            byte byteArray [9];
            Serial.println(LIDAR12_SERIAL);
            if (LIDAR12_SERIAL) {
                LIDAR.readBytes(byteArray, 9); // write output of read to an array of length 9
                Serial.println("Distance: " + (byteArray[3] << 8) | (byteArray[2] << 0));
                Serial.println("Strength: " + (byteArray[5] << 8) | (byteArray[4] << 0));
            }
            break;
        case 5:
            digitalWrite(LIDAR56_MUX, LOW);
            byte byteArray [9];
            Serial.println(LIDAR56_SERIAL);
            if (LIDAR56_SERIAL) {
                LIDAR.readBytes(byteArray, 9); // write output of read to an array of length 9
                Serial.println("Distance: " + (byteArray[3] << 8) | (byteArray[2] << 0));
                Serial.println("Strength: " + (byteArray[5] << 8) | (byteArray[4] << 0));
            }
            break;
        case 6:
            digitalWrite(LIDAR56_MUX, HIGH);
            byte byteArray [9];
            Serial.println(LIDAR56_SERIAL);
            if (LIDAR56_SERIAL) {
                LIDAR.readBytes(byteArray, 9); // write output of read to an array of length 9
                Serial.println("Distance: " + (byteArray[3] << 8) | (byteArray[2] << 0));
                Serial.println("Strength: " + (byteArray[5] << 8) | (byteArray[4] << 0));
            }
            break;
        case 7:
            check_accel();
            break;
        case 8:
            check_gyro();
            break;
        case 9:
            check_motor();
            break;
        case 10:
            check_line_sensor();
            break;
        default:
            break;
    }
}