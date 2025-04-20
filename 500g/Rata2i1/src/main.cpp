
#include <Arduino.h>
//q:what's wrong with my file



// imports
#include "motorDriver.h"
#include "robotAction.h"
#include "worldState.h"
#include "Strategies.h"
#include "lineReader.h"
#include "irSensor.h"
#include "Timer.h"

// pinouts
const int LF_IR = 2;
const int RF_IR = 3;
const int LB_IR = 4;
const int RB_IR = 5;
const int F_LINE = 14;
const int B_LINE = 15;
const int R_PWM = 6;
const int L_PWM = 9;
const int R_FWD = 19;
const int R_BWD = 20;
const int L_FWD = 21;
const int L_BWD = 22;
const int StartMod = 17;

// define objects
IRSensor *leftFrontIR;
IRSensor *rightFrontIR;
IRSensor *leftBackIR;
IRSensor *rightBackIR;
lineReader *frontLine;
lineReader *backLine;

motorDriver *leftMotorDriver;
motorDriver *rightMotorDriver;
robotAction *robot;
worldState *state;
Timer *timer;
Strategies *strategies;

void setup()
{
    // define pinmodes
    pinMode(LF_IR, INPUT);
    pinMode(RF_IR, INPUT);
    pinMode(LB_IR, INPUT);
    pinMode(RB_IR, INPUT);
    pinMode(F_LINE, INPUT);
    pinMode(B_LINE, INPUT);

    worldState::robotSensors sensors = {
        new lineReader(F_LINE),
        new lineReader(B_LINE),
        new IRSensor(LF_IR),
        new IRSensor(RF_IR),
        new IRSensor(LB_IR),
        new IRSensor(RB_IR)};
    state = new worldState(sensors);

    leftMotorDriver = new motorDriver();
    rightMotorDriver = new motorDriver();

    robot = new robotAction(leftMotorDriver, rightMotorDriver);

    timer = new Timer();

    strategies = new Strategies(state, robot, timer);

    Serial.begin(9600);

    delay(5000);

    // // wait for start signal
    // while (!digitalRead(StartMod))
    // {
    //     Serial.print(digitalRead(StartMod));
    //     Serial.println(" Waiting for start signal");
    // }
    
    
}

/**
 * Polls all sensors and prints their values to the serial monitor
 * @param debug - if true, prints sensor values to the serial monitor
 */
void pollSensors(bool debug = false)
{
    leftFrontIR->setValue(digitalRead(LF_IR));
    rightFrontIR->setValue(digitalRead(RF_IR));
    leftBackIR->setValue(digitalRead(LB_IR));
    rightBackIR->setValue(digitalRead(RB_IR));
    frontLine->setValue(analogRead(F_LINE));
    backLine->setValue(analogRead(B_LINE));

    if (debug)
    {
        Serial.print("LF: ");
        Serial.print(leftFrontIR->getValue());
        Serial.print(" RF: ");
        Serial.print(rightFrontIR->getValue());
        Serial.print(" LB: ");
        Serial.print(leftBackIR->getValue());
        Serial.print(" RB: ");
        Serial.println(rightBackIR->getValue());
    }
}

void updateState() {
    state->getEnemyPosition();
    state->getPosition();
}

void loop()
{
    pollSensors();
    updateState();
    // robot ->moveForward(255);

    // listen for stop signal
    // if (!digitalRead(StartMod)) {
    //   while(true) {
    //     brake();
    //     Serial.println("braking");
    //   }
    // }
    Serial.println("Running");

    // debug()
}

