#include "OtherPinsSetup.h"
#include "Pins.h"

void OtherPinsSetup::setup() {
    pinMode(led1, OUTPUT);
    pinMode(led2, OUTPUT);
    pinMode(servo, OUTPUT);
    pinMode(dip1, INPUT);
    pinMode(dip2, INPUT);
    pinMode(voltageDivider, INPUT);
    pinMode(startMod, INPUT);

    pinMode(button1, INPUT);
    pinMode(button2, INPUT);
    pinMode(lcd_scl, OUTPUT);
    pinMode(lcd_sda, OUTPUT);

}