#include "../include/common.h"
#include "Servo.h"
#include "Wire.h"
#include "Arduino.h"

Robot* pooki; 
// MPU6050 mpu(Wire);

bool strat_one = true;
bool strat_two = false;
bool strat_three = false;
bool strat_four = false;

    uint8_t lineSensorPins[] = {A0, A1};
    uint8_t IRpins[] = {7, 1, 4, 8, 2};
    uint8_t leftMotorPins[] = {11, 6};
    uint8_t rightMotorPins[] = {5, 3};
    uint8_t startModulePin = 10;
    uint8_t flagPin = 9;

  int leftMotorFWD = 11;
  int leftMotorREV = 6;
  int rightMotorFWD = 5;
  int rightMotorREV = 3;

void setup() {
    
  Serial.begin(9600);
  Wire.begin();

  pooki = new Robot();
    
  pooki->createLineSensors(lineSensorPins);
  pooki->createIRSensors(IRpins);
  pooki->createIMU();
  pooki->createDipSwitch(A6, A7);
  pooki->createStartModule(startModulePin);
  pooki->createMotors(leftMotorPins, rightMotorPins);
  pooki->createFlags(flagPin);


}

void boundary_maneuver_IR_detected() {
  while(pooki->getIRValues()[3]) {
    pooki->moveBackwards(255, 100);
    delay(25);
    pooki->moveForwards(255, 100);
    delay(25);
  }
}

void boundary_maneuver_IR_not_detected() {

  if (digitalRead(10)) {
      pooki->brakeHigh();
      delay(50);
      pooki->moveBackwards(205, 200);
      delay(200);
      pooki->brakeHigh();
      pooki->turnLeftNoGyro(205, 180);
      delay(50);
  }

}

void start_routine() {

  pooki->flags.deploy();

  switch (pooki->dipSwitch.getStrat())
  {
  case 1:
    pooki->moveBackwards(255, 175);
    pooki->brakeHigh();
    break;
  case 2:
    break;
  case 3:
    break;
  case 4:
    break; 
  default:
    break;
  }
}


bool ir_values_chooser(const bool desiredStates[5]) {
    const bool* currentStates = pooki->getIRValues();  // Assuming this returns a C-style array

    for (int i = 0; i < 5; ++i) {
        if (currentStates[i] != desiredStates[i]) {
            return false;
        }
    }
    return true;
}

bool pattern_one[5] = {false, true, true, true, false};
bool pattern_two[5] = {false, false, true, true, false};
bool pattern_three[5] = {false, true, true, false, false};

bool start_routine_finished = false;
bool started = false;



void loop() {

  pooki->updateState();

  // Serial.println(pooki->getStartModActivated());
  // Serial.println(digitalRead(10));


 if (digitalRead(10) && !start_routine_finished) {
       start_routine();
       start_routine_finished = true; 
  } 

     else if (digitalRead(10) && strat_one && start_routine_finished) {

      if (pooki->checkBoundary()) {
        boundary_maneuver_IR_not_detected();
      } else {
              if (pooki->checkBoundary()) {
        boundary_maneuver_IR_not_detected();
      }
        pooki->moveForwards(50);
  //         if (ir_values_chooser(pattern_one)) {
            // // pooki->moveForwards(90);

            // if (pooki->checkBoundary()) {
              // boundary_maneuver_IR_not_detected();
            // }
            // analogWrite(leftMotorFWD, 90);
            // analogWrite(leftMotorREV, 0);
            // analogWrite(rightMotorFWD, 90);
            // analogWrite(rightMotorREV, 0);
          // } 
         //  else if (ir_values_chooser(pattern_two)) {
            // if (pooki->checkBoundary()) {
              // boundary_maneuver_IR_not_detected();
            // }
            // analogWrite(leftMotorFWD, 90);
            // analogWrite(leftMotorREV, 0);
            // analogWrite(rightMotorFWD, 70);
            // analogWrite(rightMotorREV, 0);
          // } else if (ir_values_chooser(pattern_three)) {
            // if (pooki->checkBoundary()) {
              // boundary_maneuver_IR_not_detected();
            // }
            // analogWrite(leftMotorFWD, 70);
            // analogWrite(leftMotorREV, 0);
            // analogWrite(rightMotorFWD, 90);
            // analogWrite(rightMotorREV, 0);
          // }

     }
   } 
  // else if (digitalRead(10) == true && strat_two) {

  // } else if (digitalRead(10) == true && strat_three) {

  // } else if (digitalRead(10) == true && strat_four) {

  // } else {

  // }

  delay(25);
}
