#ifndef FROSTI_H
#define FROST_H

#include "Robot.h"
#include <Arduino.h>
#include <memory>
#include "sensors/TFMini/TFMini.h"
#include "sensors/LineSensor.h"
#include "sensors/StartModule.h"

#define LINE_SENSOR_1 0
#define LINE_SENSOR_2 1
#define LINE_SENSOR_3 2

#define DATA_SENSOR_1 4
#define DATA_SENSOR_2 5
#define DATA_SENSOR_3 6

#define START_MODULE 999

constexpr int LINE_THRESHOLD = 300; 

class Frosti : public Robot {

private: 
        TFMini* rightDist;
        TFMini* leftDist;
        TFMini* centerDist;

        LineSensor* lineSensor1;
        LineSensor* lineSensor2;
        LineSensor* lineSensor3;
        std::unique_ptr<StartModule> startModule;  

        int floorReading = 0; 
        int samples = 0; 

public: 
    Frosti() {
        //TODO: replace these with the actual pin values
        
        Serial1.begin(DATA_SENSOR_1); 
        Serial2.begin(DATA_SENSOR_2); 
        Serial3.begin(DATA_SENSOR_3); 

        //not used?
        Serial4.begin(115200); 

        startModule = std::make_unique<StartModule>(START_MODULE);
        leftDist = new TFMini(&Serial1);
        rightDist =  new TFMini(&Serial2); 
        centerDist =  new TFMini(&Serial3); 
        lineSensor1 = new LineSensor(LINE_SENSOR_1);
        lineSensor2 = new LineSensor(LINE_SENSOR_2);
        lineSensor3 = new LineSensor(LINE_SENSOR_3);
        _sensors.push_back(lineSensor1); 
        _sensors.push_back(lineSensor2);
        _sensors.push_back(lineSensor3);
        _sensors.push_back(leftDist); 
        _sensors.push_back(rightDist); 
        _sensors.push_back(centerDist);
    }

    void updateState() override {
        _state.distanceToEnemy.left = leftDist->GetDistance(); 
        _state.distanceToEnemy.right = rightDist->GetDistance(); 
        _state.distanceToEnemy.center = centerDist->GetDistance(); 
        //Serial.printf("Left: %d, Right: %d \n", leftDist->GetDistance(),rightDist->GetDistance());
        //Serial.printf("Left: %d, Right: %d \n", lineSensor1->GetDetection(),lineSensor2->GetDetection());
        _state.enabled = startModule->isActive(); 
        if (abs(lineSensor1->GetDetection() - floorReading) < LINE_THRESHOLD || abs(lineSensor2->GetDetection() - floorReading) < LINE_THRESHOLD
            || abs(lineSensor3->GetDetection() - floorReading) < LINE_THRESHOLD) {
            _state.atBounds = true; 
        } else {
            _state.atBounds = false; 
        }
    }

    void sampleFloor() {
        unsigned int timestamp = millis(); 
        samples = 0;
        while (millis() - timestamp < 5000) {
            lineSensor1->Poll(); 
            lineSensor2->Poll(); 
            lineSensor3->Poll();
            int leftFloor = lineSensor1->GetDetection(); 
            int rightFloor = lineSensor2->GetDetection(); 
            int centerFloor = lineSensor3->GetDetection(); 
            int avg = (leftFloor + rightFloor + centerFloor) / 3; 
            floorReading += avg; 
            samples++; 
        }
        floorReading = (floorReading / samples); 
    } 

}; 

#endif 