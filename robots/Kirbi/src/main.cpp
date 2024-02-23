#include <Arduino.h>
#include <SoftwareSerial.h>
#include <memory>

#include "MotorController.h"
#include "Robot/Kirbi.h"
#include "TFMPlus.h"

#include "Strategies/SlammyWhammy.h"
#include "Strategies/FigureEight.h"
#include "SabertoothSimplified.h"


// Init motor controller
// Make sure that everything is grounded
MotorController motorController{&Serial5};
SabertoothSimplified mc{Serial5};

Kirbi kirbi{};
TFMPlus tfm{};
SlammyWhammy strategy(75, 100);
FigureEight figureEightStrategy(100, 850);

bool hasStarted = false;

const unsigned int BACKUP_TIME = 300; // in ms
const unsigned int TURN_TIME = 200;
void setup() {
  Serial2.begin(115200);
  tfm.begin(&Serial2);
  Serial5.begin(9600);
  pinMode(A22, OUTPUT);
  analogWrite(A22, 500);
}


void loop() {
  //Serial.println("======= NEW LOOP AAAA =======");
  kirbi.UpdateSensors();
  kirbi.UpdateState();

  RobotState currentState = kirbi.GetCurrentState();

  if (currentState.enabled == 1) {
    if (!hasStarted) {
      kirbi.SampleFloor();
      hasStarted = true;
      currentState.atBounds = false;
    }
    if (currentState.atBounds) {
        Serial.println("AT BOUNDS");
    // Drive motors backwards for X amount of time
      unsigned int timestamp = millis();

      while (millis() - timestamp < BACKUP_TIME) {
        mc.motor(1, -50);
        mc.motor(2, -50);
      }

      timestamp = millis();
      while (millis() - timestamp < TURN_TIME) {
        mc.motor(1, 50);
        mc.motor(2, -50);
      }

      kirbi.UpdateSensors();
      kirbi.UpdateState();
      currentState = kirbi.GetCurrentState();
  }


    auto output = strategy.Run(currentState);
    mc.motor(1, output.currentRightMotorPow);
    mc.motor(2, output.currentLeftMotorPow);
  } else {
    mc.stop();
  }
}

/* emergency roomba strat */
// if (state.atBounds) {
//       state.backupUntilMillis = millis() + 1000;
//       state.isBackingUp = true;
//     }

//     if (state.isBackingUp) {
//       if (millis() >= state.backupUntilMillis) {
//         state.isBackingUp = false;
//       }

//       mc.motor(1, -30);
//       mc.motor(2, -30);
//     } else {
//       mc.motor(1, 100);
//       mc.motor(2, 100);
//     }
// }
