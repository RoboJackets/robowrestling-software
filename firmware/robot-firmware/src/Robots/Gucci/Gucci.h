#ifndef GUCCI_H
#define GUCCI_H

#include "Robots/Robot.h"
#include <Arduino.h>
#include "Sensors/TFMini/TFMini.h"

class Gucci : public Robot {
private: 
        TFMini* rightDist;
        TFMini* frontDist;
        TFMini* leftDist;
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

        _sensors.push_back(rightDist); // right 
        _sensors.push_back(frontDist); 
        _sensors.push_back(leftDist); 

    }

    void UpdateState() override {
        
        Serial.printf("left: %d, right: %d, front: %d \n", leftDist->GetDistance(), rightDist->GetDistance(), frontDist->GetDistance()); 
    
    } 


}; 

#endif 