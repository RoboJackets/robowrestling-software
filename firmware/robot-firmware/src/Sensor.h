#include <Wire.h>
#include <Arduino.h>

/**
 * 6 distance sensors
 * 2 line sensors
 * x encoders ?
 * 1 imu ?
*/

class Sensor {
    public:
        /**
         * @brief Parses the polled info into useful information
         * 
         * @return something?
        */
        virtual double parseData() {};

        /**
         * Constructor for Sensor class
        */
        Sensor(int rx, int tx, int bytesToPoll, HardwareSerial* serial): tx(tx), rx(rx), bytesToPoll(bytesToPoll) {
            this->serial = serial;
        }
        
    public:
        //the location of the transmission and recieving ports
        int rx;
        int tx;
      
        int bytesToPoll;

        HardwareSerial* serial;

        
        /**
         * @brief Poll from the sensor
         * 
         * @return a byte array of info
         */
        byte* pollSensor() {
            char incomingBytes[bytesToPoll];
            if (serial->available() > 0) {
                // read the incoming byte:
                serial->readBytes(incomingBytes, 9);
            }
            return (byte*) incomingBytes;
        }
        /*
        byte* pollSensor() {
            //The third 1 stops continiously requesting: https://www.arduino.cc/reference/en/language/functions/communication/wire/requestfrom/
            Wire.requestFrom(rx, bytesToPoll, 1);
            byte bytes[bytesToPoll];
            int i = 0;
            while(Wire.available()) {
                bytes[i] = Wire.read();
                i++;
            }
            return bytes;
        }*/

};