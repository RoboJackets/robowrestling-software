
#include <Arduino.h>
#include <cstdint>
#include "../include/FrankiState.h"


FrankiState::FrankiState() 
    : _lineSensorLeft(LINE_SENSOR_LEFT), 
    _lineSensorRight(LINE_SENSOR_RIGHT), 
    _startModule(START_MODULE_PIN), 
    _js40Left(PIN_JS40F_LEFT_PIN), 
    _js40MidLeft(PIN_JS40F_MID_LEFT_PIN), 
    _js40Middle(PIN_JS40F_MID), 
    _js40MidRight(PIN_JS40F_MID_RIGHT), 
    _js40Right(PIN_JS40F_RIGHT)
{
    pinMode(PIN_JS40F_LEFT_PIN, INPUT);
    pinMode(PIN_JS40F_MID_LEFT_PIN, INPUT);
    pinMode(PIN_JS40F_MID, INPUT);
    pinMode(PIN_JS40F_MID_RIGHT, INPUT);
    pinMode(PIN_JS40F_RIGHT, INPUT);

    pinMode(LINE_SENSOR_LEFT, INPUT);
    pinMode(LINE_SENSOR_RIGHT, INPUT);

    pinMode(START_MODULE_PIN, INPUT);
}

void FrankiState::updateState() {
    FrankiState::_lineSensorLeftValue = FrankiState::_lineSensorLeft.getValue();
    FrankiState::_lineSensorRightValue = FrankiState::_lineSensorRight.getValue();

    FrankiState::objectDetectedLeft = FrankiState::_js40Left.objectDetected();
    FrankiState::objectDetectedMidLeft = FrankiState::_js40MidLeft.objectDetected();
    FrankiState::objectDetectedMiddle = FrankiState::_js40Middle.objectDetected();
    FrankiState::objectDetectedMidRight = FrankiState::_js40MidRight.objectDetected();
    FrankiState::objectDetectedRight = FrankiState::_js40Right.objectDetected();

    FrankiState::startModuleActive = FrankiState::_startModule.isActive();

    FrankiState::setAtBounds(FrankiState::_lineSensorLeft.lineDetected() || FrankiState::_lineSensorRight.lineDetected());
        
}

