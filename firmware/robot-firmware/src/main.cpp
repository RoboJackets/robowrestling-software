#include <Arduino.h>
#include <memory>

#include "Sensor.h"

Sensor sensor{0,0,9,&Serial2};

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  Serial2.begin(115200);
}

void loop() {
  byte* bytes = sensor.pollSensor();
  Serial.write(bytes, 9);
}