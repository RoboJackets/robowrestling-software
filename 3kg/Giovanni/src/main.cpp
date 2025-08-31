#include <Arduino.h>

// Output Pins
int leftMotor = 0;
int rightMotor = 1;


// Input Pins
int left90IR = 2;
int right90IR = 3;
int left60IR = 4;
int right60IR = 5;
int left30IR = 6;
int right30IR = 7;
int centerIR = 8;

int frLine = 9;
int flLine = 10;
int brLine = 11;
int blLine = 12;

// Sensor Reading



void setup() {
  // Pin Outs
  pinMode(leftMotor, OUTPUT);
  pinMode(rightMotor, OUTPUT);

  // Pin Inputs
  pinMode(left90IR, INPUT);
  pinMode(right90IR, INPUT);
  pinMode(left60IR, INPUT);
  pinMode(right60IR, INPUT);
  pinMode(left30IR, INPUT);
  pinMode(right30IR, INPUT);
  pinMode(centerIR, INPUT);

  pinMode(frLine, INPUT);
  pinMode(flLine, INPUT);
  pinMode(brLine, INPUT);
  pinMode(blLine, INPUT);
}

void loop() {
  pollSensors();
  calcState();
  writeMotors();
}

void pollSensors() {

}

void calcState() {

}

void writeMotors() {

}