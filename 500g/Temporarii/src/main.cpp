#include <Arduino.h>
#include "Robot/Temporarii.h"

Temporarii *temporarii = new Temporarii();
// put your setup code here, to run once:
void setup() {

}

// put your main code here, to run repeatedly:
String startState = "Searching";
WorldState *state = new WorldState();
void loop() {
  if (startState == "Searching") {
    // Implement World State
  } else if (startState == "Approach") {

  } else if (startState == "Push") {

  } else {
    
  }
  /*
  if (digitalRead(MID_IR_PIN) == 1) {
    //Set robot to full power (100)
    analogWrite(LEFT_MOTOR_PIN, 100);
    analogWrite(RIGHT_MOTOR_PIN, 100);
  } else {
    if (shifting) {
      analogWrite(LEFT_MOTOR_PIN, 50);
      analogWrite(RIGHT_MOTOR_PIN, 80);
      shifting = false;
    } else {
      analogWrite(LEFT_MOTOR_PIN, 80);
      analogWrite(RIGHT_MOTOR_PIN, 50);
      shifting = true;
    }
  }
  */
}