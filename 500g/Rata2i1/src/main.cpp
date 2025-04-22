
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
const int LF_IR = 3;
const int RF_IR = 4;
const int LB_IR = 2;
const int RB_IR = 5;
const int F_LINE = 14;
const int B_LINE = 15;
const int R_PWM = 6;
const int L_PWM = 9;
const int R_FWD = 20;
const int R_BWD = 19;
const int L_FWD = 22;
const int L_BWD = 21;
const int StartMod = 17;
bool start = true;

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
    pinMode(R_PWM, OUTPUT);
    pinMode(L_PWM, OUTPUT);
    pinMode(R_FWD, OUTPUT);
    pinMode(R_BWD, OUTPUT);
    pinMode(L_FWD, OUTPUT);
    pinMode(L_BWD, OUTPUT);

    leftMotorDriver = new motorDriver();
    rightMotorDriver = new motorDriver();
    frontLine = new lineReader(analogRead(F_LINE), 600);
    backLine = new lineReader(analogRead(B_LINE), 600);
    rightBackIR = new IRSensor(digitalRead(RB_IR));
    leftBackIR = new IRSensor(digitalRead(LB_IR));
    rightFrontIR = new IRSensor(digitalRead(RF_IR));
    leftFrontIR = new IRSensor(digitalRead(LF_IR));

    worldState::robotSensors sensors = {
        frontLine,
        backLine,
        leftFrontIR,
        rightFrontIR,
        leftBackIR,
        rightBackIR
    };
    state = new worldState(sensors);


    robot = new robotAction(leftMotorDriver, rightMotorDriver);

    timer = new Timer();

    strategies = new Strategies(state, robot, timer);

    Serial.begin(9600);

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
        Serial.print(rightBackIR->getValue());
        Serial.print(" F_LINE: ");
        Serial.print(frontLine->getValue());
        Serial.print(" B_LINE: ");
        Serial.print(backLine->getValue());
        Serial.print(" F_LINE RAW: ");
        Serial.print(analogRead(F_LINE));
        Serial.print(" B_LINE RAW: ");
        Serial.println(analogRead(B_LINE));


    }
}

void updateState(bool debug = false) {
    state->getEnemyPosition();
    state->getPosition();

    if (debug) {
        Serial.print("Enemy Position: ");
        Serial.print(state->getEnemyPosition());
        Serial.print(" Position: ");
        Serial.println(state->getPosition());
    }
}

void updateMotorSpeed() {
    analogWrite(L_PWM, leftMotorDriver->getSpeed());
    analogWrite(R_PWM, rightMotorDriver->getSpeed());
    digitalWrite(L_FWD, leftMotorDriver->getFwd());
    digitalWrite(L_BWD, leftMotorDriver->getBwd());
    digitalWrite(R_FWD, rightMotorDriver->getFwd());
    digitalWrite(R_BWD, rightMotorDriver->getBwd());
}

void loop()
{
    if (start) {
        robot->moveForward(255); 
        updateMotorSpeed();
        delay(1000);
        start = false;
    }
    pollSensors(true);
    updateState();

    strategies->generalStrategy();
    updateMotorSpeed(); 
    



    //turn on teensy led
    // digitalWrite(LED_BUILTIN, HIGH);
    

    // listen for stop signal
    // if (!digitalRead(StartMod)) {
    //   while(true) {
    //     robot->stop();
    //     updateMotorSpeed();
    //     Serial.println("braking");
    //   }
    // }

    // debug()
}

