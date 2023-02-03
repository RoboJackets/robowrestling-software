#include <Arduino.h>
#include <SoftwareSerial.h>
#include <memory>

#include "MotorController/MotorController.h"
#include <TFMPlus.h>
#include "Robots/Gucci/Gucci.h"


// Init motor controller
// Make sure that everything is grounded
Gucci gucci{};  
int16_t dist = -1;
void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
}

void loop() {
  gucci.UpdateSensors(); 
}

