#include "Motors.h"
#include "Pins.h"

// ===== MOTOR TRIM ==== (We will use this to compensate for any physical motor differences)
#define RPOS_TRIM 0
#define RNEG_TRIM 0
#define LPOS_TRIM 0
#define LNEG_TRIM 0

static int rpSpeed(int s) { return constrain(s + RPOS_TRIM, 0, 255); }
static int rnSpeed(int s) { return constrain(s + RNEG_TRIM, 0, 255); }
static int lpSpeed(int s) { return constrain(s + LPOS_TRIM, 0, 255); }
static int lnSpeed(int s) { return constrain(s + LNEG_TRIM, 0, 255); }


void Motors::setup() {
    pinMode(Rpos, OUTPUT);
    pinMode(Rneg, OUTPUT);
    pinMode(Lpos, OUTPUT);
    pinMode(Lneg, OUTPUT);
}

void Motors::stop() {
    analogWrite(Rpos, 0);
    analogWrite(Rneg, 0);
    analogWrite(Lpos, 0);
    analogWrite(Lneg, 0);
}

void Motors::forward(int speed) {
    analogWrite(Rpos, rpSpeed(speed));
    analogWrite(Lpos, lpSpeed(speed));
    analogWrite(Rneg, 0);
    analogWrite(Lneg, 0);
}

void Motors::back(int speed) {
    analogWrite(Rpos, 0);
    analogWrite(Lpos, 0);
    analogWrite(Rneg, rnSpeed(speed));
    analogWrite(Lneg, lnSpeed(speed));
}

void Motors::rotateRight(int speed) {
    analogWrite(Rpos, 0);
    analogWrite(Rneg, rnSpeed(speed));
    analogWrite(Lpos, lpSpeed(speed));
    analogWrite(Lneg, 0);
}

void Motors::rotateLeft(int speed) {
    analogWrite(Rpos, rpSpeed(speed));
    analogWrite(Rneg, 0);
    analogWrite(Lpos, 0);
    analogWrite(Lneg, lnSpeed(speed));
}

void Motors::slowLeft(int speed) {
    analogWrite(Rpos, rpSpeed(speed));
    analogWrite(Rneg, 0);
    analogWrite(Lpos, 0);
    analogWrite(Lneg, 0);
}

void Motors::slowRight(int speed) {
    analogWrite(Rpos, 0);
    analogWrite(Rneg, 0);
    analogWrite(Lpos, lpSpeed(speed));
    analogWrite(Lneg, 0);
}


//Line Functions - We should define how we want these to act when it interacts with the line.
void Motors::lineLeftTurn(int speed) {
    back(140);
    delay(100);
    rotateRight(240);
    delay(50);
    stop();
}

void Motors::lineRightTurn(int speed) {
    back(140);
    delay(100);
    rotateLeft(240);
    delay(50);
    stop();
}

void Motors::lineMiddleTurn(int speed) {
    forward(100);
    delay(50);
    stop();
}

