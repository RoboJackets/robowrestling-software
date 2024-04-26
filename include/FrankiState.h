#include <Arduino.h>
#include "Sensors/LineSensor.h"
#include "Sensors/StartModule.h"
#include "Sensors/JS40.h"

#pragma once

#define PIN_JS40F_LEFT_PIN 23 
#define PIN_JS40F_MID_LEFT_PIN 22
#define PIN_JS40F_MID 21
#define PIN_JS40F_MID_RIGHT 20
#define PIN_JS40F_RIGHT 19

#define LINE_SENSOR_LEFT 18 
#define LINE_SENSOR_RIGHT 17 

#define START_MODULE_PIN 16

struct FrankiState {
    private:
        bool _atBounds;
        LineSensor _lineSensorLeft;
        LineSensor _lineSensorRight;
        StartModule _startModule;
        JS40 _js40Left;
        JS40 _js40MidLeft;
        JS40 _js40Middle;
        JS40 _js40MidRight;
        JS40 _js40Right;

        u_int16_t _lineSensorLeftValue;
        u_int16_t _lineSensorRightValue;

        bool objectDetectedLeft;
        bool objectDetectedMidLeft;
        bool objectDetectedMiddle;
        bool objectDetectedMidRight;
        bool objectDetectedRight;

        bool startModuleActive;

    public:
        FrankiState();

        void updateState();

        LineSensor getLineSensorLeft() { return _lineSensorLeft; }
        LineSensor getLineSensorRight() { return _lineSensorRight; }

        StartModule getStartModule() { return _startModule; }

        JS40 getJS40Left() { return _js40Left; }
        JS40 getJS40MidLeft() { return _js40MidLeft; }
        JS40 getJS40Middle() { return _js40Middle; }
        JS40 getJS40MidRight() { return _js40MidRight; }
        JS40 getJS40Right() { return _js40Right; }

        bool startModuleIsActive() { return startModuleActive; }

        bool isAtBounds() { return _atBounds; }

        void setAtBounds(bool atBounds) { _atBounds = atBounds; }

        bool leftIRDetected () { return objectDetectedLeft; }
        bool midLeftIRDetected () { return objectDetectedMidLeft; }
        bool midIRDetected () { return objectDetectedMiddle; }
        bool midRightIRDetected () { return objectDetectedMidRight; }
        bool rightIRDetected () { return objectDetectedRight; }

};