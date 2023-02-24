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
  Serial.begin(115200);
  Serial1.begin(115200);
  Serial2.begin(115200);
  Serial3.begin(115200); 
  //motorControllerSerial -> begin(9600);
  tfMini = new TFMini(&Serial1);
  mux1 = new LidarMux(28, tfMini);
}
String out1 = "Lidar one: ";
String out2 = ", Lidar two: ";
void loop() {
  Serial.println("======= NEW LOOP AAAA =======");
 // mux1->readLidars(x);
 // String out =  out1 + x->lidarOne + out2 + x->lidarTwo;
 // Serial.println(out);
 //gucci.UpdateSensors();
  auto pair = mux1->readLidars();
  Serial.printf("one: %d, two: %d \n", pair.first.dist, pair.second.dist);
  delay(5000);
}