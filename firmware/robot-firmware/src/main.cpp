#include <Arduino.h>
#include <SoftwareSerial.h>
#include <memory>

#include "MotorController/MotorController.h"
#include "Sensors/TFMini/TFMini.h"
#include "Sensors/LidarMux.h"

#include "Robots/Gucci/Gucci.h"

// Init motor controller
// Make sure that everything is grounded
SoftwareSerial* motorControllerSerial = new SoftwareSerial(11, 2); // tx on pin 2, rx on pin 11 (not needed)
MotorController motorController{motorControllerSerial};
TFMini* tfMini;
LidarMux* mux1;
Gucci gucci{};
int16_t dist = -1;
void setup() {
  // put your setup code here, to run once:
  //motorControllerSerial -> begin(9600);

}

void loop() {
  Serial.println("======= NEW LOOP AAAA =======");
  mux1->readLidars(x);
  String out =  out1 + x->lidarOne + out2 + x->lidarTwo;
  Serial.println(out);
  gucci.UpdateSensors();
  delay(5000);
}

