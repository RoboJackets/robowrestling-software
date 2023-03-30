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
        Serial3.begin(115200); 
        Serial4.begin(115200); 

        startModule = std::make_unique<StartModule>(14);
        leftDist = new TFMini(&Serial2);
        rightDist =  new TFMini(&Serial3); 
        lineSensor1 = new LineSensor(23);
        lineSensor2 = new LineSensor(35);


        _sensors.push_back(lineSensor1); 
        _sensors.push_back(lineSensor2);

    }

    void UpdateState() override {
        _state.lidars[0] = 0xFFFF; 
        _state.lidars[1] = 0xFFFF; 
        _state.lidars[2] = leftDist->GetDistance(); 
        _state.lidars[3] = rightDist->GetDistance(); 
        _state.lidars[4] = 0xFFFF;
        _state.lidars[5] = 0xFFFF;  

        Serial.printf("%d \n", leftDist->GetDistance());
        _state.enabled = startModule->isActive(); 
        _state.atBounds = lineSensor1->GetDetection() || lineSensor2->GetDetection(); 
    } 


}; 

#endif 