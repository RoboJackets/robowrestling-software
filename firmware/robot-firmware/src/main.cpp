#include <Arduino.h>
#include <SoftwareSerial.h>
#include <memory>

#include "MotorController/MotorController.h"
#include "Robots/Gucci/Gucci.h"
#include "TFMPlus.h"

#include "Strategies/SlammyWhammy/SlammyWhammy.h"
#include "SabertoothSimplified.h"


// Init motor controller
// Make sure that everything is grounded
MotorController motorController{&Serial5};
SabertoothSimplified mc{Serial5};

Gucci gucci{};
TFMPlus tfm{};
SlammyWhammy<RobotState, RobotState> strategy(10, 20);

void setup() {
  Serial2.begin(115200);
  tfm.begin(&Serial2);
  Serial5.begin(9600);
}


void loop() {
  //Serial.println("======= NEW LOOP AAAA =======");
  gucci.UpdateSensors();
  gucci.UpdateState();

  auto state = gucci.GetCurrentState();
  Serial.printf("%d \n", state.enabled);
  if (state.enabled == 1) {

    if (state.atBounds) {
      state.backupUntilMillis = millis() + 1000;
      state.isBackingUp = true;
    }

    if (state.isBackingUp) {
      if (millis() >= state.backupUntilMillis) {
        state.isBackingUp = false;
      }

      mc.motor(1, -30);
      mc.motor(2, -30);
    } else {
      mc.motor(1, 100);
      mc.motor(2, 100);
    }

  } else {
    mc.stop();
  }


  delay(50);

}
