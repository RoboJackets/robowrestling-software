#include "Sensors.h"
#include "Pins.h"

void Sensors::setup() {
    pinMode(lLine, INPUT);
    pinMode(rLine, INPUT);
    pinMode(mLine, INPUT);

    pinMode(center, INPUT);
    pinMode(lFront, INPUT);
    pinMode(lSide, INPUT);
    pinMode(rFront, INPUT);
    pinMode(rSide, INPUT);
}

bool Sensors::lLineDetected() {
    return analogRead(lLine) < 100;
}

bool Sensors::rLineDetected() {
    return analogRead(rLine) < 100;
}

bool Sensors::mLineDetected() {
    return analogRead(mLine) < 100;
}
