#include <Arduino.h>
#include <SoftwareSerial.h>
#include <memory>

#include "MotorController/MotorController.h"
//#include <TFMPlus.h>
#include "Sensors/TFMini/TFMini.h"
#include "Sensors/LidarMux.h"

// Init motor controller
// Make sure that everything is grounded
SoftwareSerial* motorControllerSerial = new SoftwareSerial(11, 2); // tx on pin 2, rx on pin 11 (not needed)
MotorController motorController{motorControllerSerial};
TFMini* tfMini;
LidarMux* mux1;

void setup() {
  tfMini = new TFMini(9, 10);
  mux1 = new LidarMux(25, tfMini);
  // put your setup code here, to run once:
  Serial.begin(9600);
  Serial1.begin(115200);
  Serial2.begin(115200);
  //motorControllerSerial -> begin(9600);

}
String out1 = "Lidar one: ";
String out2 = ", Lidar two: ";
struct twoValues* x = new twoValues;
void loop() {
  mux1->readLidars(x);
  String out =  out1 + x->lidarOne + out2 + x->lidarTwo;
  Serial.println(out);
}

