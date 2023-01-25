#ifndef GUCCI_H
#define GUCCI_H

#include "Robots/Robot.h"
#include "Sensors/TFMini/TFMini.h"

class Gucci : public Robot {
private: 
        TFMini* rightDist;
        TFMini* frontDist;
        TFMini* leftDist;
public: 
    Gucci() {
        //TODO: replace these with the actual pin values
        rightDist = new TFMini(0, 1); 
        frontDist = new TFMini(0, 1); 
        leftDist = new TFMini(0, 1); 

        _sensors.push_back(rightDist); // right 
        _sensors.push_back(frontDist); 
        _sensors.push_back(leftDist); 

    }

    void UpdateState() override {
        
        Serial.printf("left: %d, right: %d, front: %d \n", leftDist->GetDistance(), rightDist->GetDistance(), frontDist->GetDistance()); 
    
    } 


}; 

#endif 