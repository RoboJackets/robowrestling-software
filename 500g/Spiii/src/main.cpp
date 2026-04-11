#include <Arduino.h>

#include "Pins.h"
#include "Motors.h"
#include "Sensors.h"
#include "OtherPinsSetup.h"
//Import States as well once its created

Motors motors;
Sensors sensor;
OtherPinsSetup otherPins;
//Create a states object as well
//int myFunction(int, int); [=====Aadi - I dont know what this is=========]

void setup() {
  while(!digitalRead(startMod)) {}

  delay(5000);
  //We should also initialise the SERVO here. I think we might need to import a servo library
  int dip1Read = digitalRead(dip1);
  int dip2Read = digitalRead(dip2);
  int button1Read = digitalRead(button1);
  int button2Read = digitalRead(button2);
}

void loop() {

  int lSideRead = digitalRead(lSide);
  int rSideRead = digitalRead(rSide);
  int lFrontRead = digitalRead(lFront);
  int rFrontRead = digitalRead(rFront);
  int centerRead = digitalRead(center);
  bool lLineRead = sensor.lLineDetected();
  bool mLineRead = sensor.mLineDetected();
  bool rLineRead = sensor.rLineDetected();

}

// put function definitions here:
int myFunction(int x, int y) {
  return x + y;
}