#include <Arduino.h>
#include <memory>

#include "Sensors/SerialSensor.h"
#include <TFMPlus.h>


SerialSensor sensor{&Serial1, 9};

int distance = 0; 
int distanceword = 0;
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Serial1.begin(115200);
  Serial2.begin(115200);
}

void loop() {
  sensor.Poll();
  byte* bytes = sensor.GetBytes(); 
  //Serial.println("as");
  distanceword = ((int) bytes[3] << 8) | ((int) bytes[2]);

  Serial.printf("Bytes[2]: %d, Bytes[3]: %d \n", bytes[6], bytes[7]);
}