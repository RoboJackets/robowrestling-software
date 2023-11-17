#include <Arduino.h>
#include <SoftwareSerial.h>
#include <memory>
#include "Frosti.h"
#include <SabertoothSimplified/SabertoothSimplified.h>
#include "MotorController.h"
#include "strategy/Strategy.h"

Frosti* frosti = new Frosti();

//Motor
MotorController motorController{&Serial5};
SabertoothSimplified mc{Serial5};

//Strategy
Strategy strategy{};

//Sensors
TFMPlus tfm{};

const unsigned int BACKUP_TIME = 300; // in ms
const unsigned int TURN_TIME = 200;
bool hasStarted = false;

// don't understand any of this
void setup() {
    Serial2.begin(115200);
    tfm.begin(&Serial2);
    Serial5.begin(9600);
    pinMode(A22, OUTPUT);
    analogWrite(A22, 500);
}

void loop() {
    frosti->updateSensors();
    frosti->updateState();

    if (frosti->getState().enabled == true) {
        if (!hasStarted) {
            frosti->sampleFloor();
            hasStarted = true;
            frosti->getState().atBounds = false;
        }
        if (frosti->getState().atBounds) {
            // Drive motors backwards for X amount of time
            unsigned int timestamp = millis();

            while (millis() - timestamp < BACKUP_TIME) {
                mc.motor(1, 100);
                mc.motor(2, -100);
            }

            timestamp = millis();
            while (millis() - timestamp < TURN_TIME) {
                mc.motor(1, 100);
                mc.motor(2, 100);
            }

        frosti->updateSensors();
        frosti->updateState();
    }


        strategy.run(frosti);
        mc.motor(1, -frosti->getState().currentRightMotorPow);
        mc.motor(2, frosti->getState().currentLeftMotorPow);
    } else {
        mc.stop();
    }
}