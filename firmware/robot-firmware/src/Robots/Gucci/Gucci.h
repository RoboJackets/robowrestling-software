#ifndef GUCCI_H
#define GUCCI_H

#include "Robots/Robot.h"
#include <Arduino.h>
#include <memory>
#include "Sensors/TFMini/TFMini.h"
#include "Sensors/LineSensor.h"
#include "Sensors/StartModule.h"

class Gucci : public Robot {
private: 
        TFMini* rightDist;
        TFMini* frontDist;
        TFMini* frontDist2;
        TFMini* leftDist;

        LineSensor* lineSensor1;
        LineSensor* lineSensor2;
        std::unique_ptr<StartModule> startModule; 
         




public: 
    Gucci() {
        //TODO: replace these with the actual pin values
        
        Serial1.begin(115200); 
        Serial2.begin(115200); 
        Serial2.setTimeout(30); 
        Serial3.begin(115200); 
        Serial4.begin(115200); 

        startModule = std::make_unique<StartModule>(14);

        
        frontDist = new TFMini(&Serial1); 
        frontDist2 = new TFMini(&Serial4);
        rightDist = new TFMini(&Serial2);
        leftDist =  new TFMini(&Serial3); 
        lineSensor1 = new LineSensor(23);
        lineSensor2 = new LineSensor(35);

        pinMode(2, OUTPUT); 
        digitalWrite(2, HIGH); 

        //_sensors.push_back(frontDist); // right 
        //_sensors.push_back(frontDist2); 
        _sensors.push_back(rightDist); 

        _sensors.push_back(lineSensor1); 
        _sensors.push_back(lineSensor2);

    }

    void UpdateState() override {
        
        Serial.printf("%d \n", rightDist->GetDistance()); 
        //Serial.printf("left: %d, right: %d, front: %d \n", leftDist->GetDistance(), rightDist->GetDistance(), frontDist->GetDistance()); 
        //Serial.printf("LineSensor1: %d, LineSensor2: %d \n", lineSensor1->GetDetection(), lineSensor2->GetDetection());
        //Serial.println(startModule->getValue());
    } 


}; 

#endif 