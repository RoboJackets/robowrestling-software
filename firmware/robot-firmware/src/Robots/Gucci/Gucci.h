#ifndef GUCCI_H
#define GUCCI_H

#include "Robots/Robot.h"
#include <Arduino.h>
#include "Sensors/TFMini/TFMini.h"
#include "Sensors/LineSensor.h"

class Gucci : public Robot {
private: 
        TFMini* rightDist;
        TFMini* frontDist;
        TFMini* leftDist;

        LineSensor* lineSensor1;
        LineSensor* lineSensor2;  


public: 
    Gucci() {
        //TODO: replace these with the actual pin values
        
        Serial1.begin(115200); 
        Serial2.begin(115200); 
        Serial3.begin(115200); 

        pinMode(2, OUTPUT);  
        pinMode(25, OUTPUT); 
        pinMode(28, OUTPUT); 

        digitalWrite(2, HIGH);
        digitalWrite(25, HIGH);
        digitalWrite(28, HIGH);

        rightDist = new TFMini(&Serial1);
        frontDist = new TFMini(&Serial2); 
        leftDist =  new TFMini(&Serial3); 

        lineSensor1 = new LineSensor(23);
        lineSensor2 = new LineSensor(35);

        _sensors.push_back(rightDist); // right 
        _sensors.push_back(frontDist); 
        _sensors.push_back(leftDist); 

        _sensors.push_back(lineSensor1); 
        _sensors.push_back(lineSensor2);

    }

    void UpdateState() override {
        
        //Serial.printf("left: %d, right: %d, front: %d \n", leftDist->GetDistance(), rightDist->GetDistance(), frontDist->GetDistance()); 
        //Serial.printf("LineSensor1: %d, LineSensor2: %d \n", lineSensor1->GetDetection(), lineSensor2->GetDetection());
    } 


}; 

#endif 