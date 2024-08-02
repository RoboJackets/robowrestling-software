#include <Arduino.h>
#include "Sensors/LineSensor.h"
#include "Sensors/StartModule.h"
#include "Sensors/JS40.h"
#include "FrankiState.h"

#pragma once

#define PIN_MOTOR_LEFT_FORWARD_PIN 4
#define PIN_MOTOR_LEFT_REVERSE_PIN 3 

#define PIN_MOTOR_RIGHT_FORWARD_PIN 6
#define PIN_MOTOR_RIGHT_REVERSE_PIN 5

// Franki class defines more of the behavior, while state is more of the current properties of the robot
class FrankiAction {
    private:         
        FrankiState _robotState;
    
    public: 

        FrankiAction();

        // sensor related
        void sampleFloor();

        void printValuesAnalog(u_int8_t pin);
        void printValuesDigital(u_int8_t pin);

        // motor control
        void stop();

        void search();
        
        void boundaryDetectedManuever();
        void moveBackwards();
        void boundaryDetectedTurn();

        void fullFowards();
        void slowerForwards();

        void detectionManeuver();

        void sharpLeft();
        void sharpRight();

        void left();
        void right();

        void slightLeft();
        void slightRight();
        
};

