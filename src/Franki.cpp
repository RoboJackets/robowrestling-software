#include <Arduino.h>
#include "../include/Franki.h"


void Franki::sampleFloor() {

    int blackReading = 0;
    int sampleCount = 100;

    for (int i = 0; i < sampleCount; i++)
    {
        int leftValue = Franki::_lineSensorLeft.getValue();
        int rightValue = Franki::_lineSensorRight.getValue();

        int average = (leftValue + rightValue) / 2;          
        blackReading += average;

        delay(5);
    }

    blackReading /= sampleCount;            
    Franki::_lineSensorLeft.setBlackReading(blackReading);
    Franki::_lineSensorRight.setBlackReading(blackReading);

}    
