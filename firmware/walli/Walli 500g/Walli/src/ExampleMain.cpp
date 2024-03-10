#include <Arduino.h>
#include <SoftwareSerial.h>

/*
    Left and right are from Scummi's perspective

    -- Digital pins --
    Pin 5 - Left line sensor
    Pin 7 - Right line sensor
    Pin 8 - Speaker (loud)

    -- Analog pins --
    Pin A1 - Right wheel forwards
    Pin A2 - Right wheel backwards
    Pin A3 - Left wheel forwards
    Pin A4 - Left wheel backwards

    Pin A5 - Left lidar sensor
    Other lidars unknown
*/

int move_speed = 650;

void setup() {
    pinMode(A1, OUTPUT);
    pinMode(A2, OUTPUT);
    pinMode(A3, OUTPUT);
    pinMode(A4, OUTPUT);

    // Pins default to INPUT, so pins
    // 5 and 7 do not need to be set
    // to input using pinMode()

    Serial.begin(9600); // for the serial monitor
}

void loop() {
    // Basic roomba strat
    int rightLine = digitalRead(7);
    int leftLine = digitalRead(5);

    if (leftLine) {
        analogWrite(A1, move_speed);
        analogWrite(A2, 0);
        analogWrite(A3, 0);
        analogWrite(A4, move_speed);
    } else if (rightLine) {
        analogWrite(A1, 0);
        analogWrite(A2, move_speed);
        analogWrite(A3, move_speed);
        analogWrite(A4, 0);
    } else {
        analogWrite(A1, move_speed);
        analogWrite(A2, 0);
        analogWrite(A3, 0);
        analogWrite(A4, move_speed);
    }

    delay(250);
}