#include <Arduino.h>
#include <SoftwareSerial.h>
#include <memory>

#include "MotorController/MotorController.h"
#include "Sensors/SerialSensor.h"
#include "TFMini/TFMini.h"


SerialSensor sensor{&Serial1, 9};

// Init motor controller
// Make sure that everything is grounded
SoftwareSerial* motorControllerSerial = new SoftwareSerial(11, 2); // tx on pin 2, rx on pin 11 (not needed)
MotorController motorController{motorControllerSerial};

int distance = 0;
int distanceword = 0;
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Serial1.begin(115200);
  Serial2.begin(115200);
  motorControllerSerial -> begin(9600);
}

void loop() {
  sensor.Poll();
  byte* bytes = sensor.GetBytes();
  //Serial.println("as");
  distanceword = ((int) bytes[3] << 8) | ((int) bytes[2]);

  motorController.move(50);
  Serial.printf("Bytes[2]: %d, Bytes[3]: %d \n", bytes[6], bytes[7]);
}
