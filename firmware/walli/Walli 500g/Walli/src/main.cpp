#include <SoftwareSerial.h>
#include <Robot/Walli.h>
#include <Strategies/Escape.cpp>
#include <Strategies/Matador.cpp>
#include <Strategies/SlamAttack.cpp>
#include <State Machine/StateController.h>
#include <State Machine/StateS.h>

/*This is the main file that runs all the code.
* the setup() method initializes variables and pinmodes
* the loop() method controls switching between strategies
*/

Walli* walli;
StateS* attack;
StateS* escape;
StateS* off;
StateController *sc;
Matador* m;
SlamAttack* slam;
Escape* e;

//storing the pins for better readability and easy changes
int leftLidarPin = A4;
int centerLidarPin = A5;
int rightLidarPin = A6;
int topLeftLinePin = A9;
int bottomLeftLinePin = A11;
int bottomRightLinePin = A12;
int leftMotorPin1 = A0;
int leftMotorPin2 = A1;
int rightMotorPin1 = A2;
int rightMotorPin2 = A3;
int startModulePin = A13; //CHANGE THIS TO THE ACTUAL PIN

//before the bot actually goes
void setup() {
    //initialize WALLI
    walli = new Walli(leftLidarPin, centerLidarPin, rightLidarPin, 
                        topLeftLinePin, bottomRightLinePin, 
                        leftMotorPin1, leftMotorPin2, rightMotorPin1, rightMotorPin2);
    //initialize Walli's control states
    sc = new StateController();
    off = new StateS(sc->getCurrent());
    attack = new StateS(State::ATTACK);
    escape = new StateS(State::ESCAPE);
    
    //off -> attack <-> escape
    off->setNext(attack);
    attack->setNext(escape);
    escape->setNext(attack);

    //objects that run the strategies
    //slam <-> escape
    slam = new SlamAttack(walli);
    e = new Escape(walli);
    Serial.begin(9600);

    
}

//while the bot goes
void loop() {
    //test file
    //walli->forward();
    //emergency case

    //while we receive no signal from the start module
    while (digitalRead(startModulePin) == 0) {
        //do nothing
        sc->setCurrent(off);
        walli->off();
    }
    //once we do receive input, start stuff
    while (digitalRead(startModulePin) == 1) {
        if (walli->onFrontLine() || walli->onBackLine()) {
            sc->setCurrent(escape);
        }
        //this runs whatever method is associated with the current state
        switch(sc->getCurrent()) {
            case OFF:
                off->setCondition(true);
                break;
            case ATTACK:
                //set to false
                attack->setCondition(false);
                //what the team calls "slammy whammy"
                slam->run();
                //set to true
                attack->setCondition(true);
                break;
            case ESCAPE:
                //set to false
                escape->setCondition(false);
                //we hit a line, need to back up
                e->run();
                //set to true
                escape->setCondition(true);
                break;
        }
        //note that when the switch is done running, the SC will be ready to transition (hopefully)
        sc->transition();
    }
}