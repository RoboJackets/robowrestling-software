#include <Arduino.h>
#include <SoftwareSerial.h>
#include <memory>

#include "MotorController/MotorController.h"
#include <TFMPlus.h>


// Init motor controller
// Make sure that everything is grounded
SoftwareSerial* motorControllerSerial = new SoftwareSerial(11, 2); // tx on pin 2, rx on pin 11 (not needed)
MotorController motorController{motorControllerSerial};

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Serial1.begin(115200);
  Serial2.begin(115200);
  motorControllerSerial -> begin(9600);
}

void loop() {
  motorController.move(50);
}

