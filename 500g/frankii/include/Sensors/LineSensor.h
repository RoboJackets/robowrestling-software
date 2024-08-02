#include <Arduino.h>
#include <cstdint>

#pragma once


class LineSensor {
    private:
        u_int16_t _value; // max value of 65535
        u_int16_t _threshold;
        u_int16_t _blackReading;

        // const variables can't be reassigned, useful for pins
        // max value of 255
        const u_int8_t _signalPin; 

    public:
        LineSensor();
        LineSensor(u_int8_t signalPin);

        u_int16_t getValue();
        bool lineDetected();
        void setThreshold(u_int16_t threshold);
        void setBlackReading(u_int16_t blackReading);
        u_int16_t getBlackReading();
        u_int16_t getThreshold();
};

