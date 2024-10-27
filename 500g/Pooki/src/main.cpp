#include "../include/common.h"

  bool flags_deployed = false;
  IRSensor rightSensor(2);
  Flags flags(9);

void setup() {
  // put your setup code here, to run once:
}

void loop() {
  // put your main code here, to run repeatedly:
  if (rightSensor.getValue() && !flags_deployed) {
    flags.deploy();
  }
  delay(500);
}