#include <Arduino.h>
#include "../include/FrankiAction.h"


FrankiAction::FrankiAction() {
  pinMode(PIN_MOTOR_LEFT_FORWARD_PIN, OUTPUT);
  pinMode(PIN_MOTOR_LEFT_REVERSE_PIN, OUTPUT);
  pinMode(PIN_MOTOR_RIGHT_FORWARD_PIN, OUTPUT);
  pinMode(PIN_MOTOR_RIGHT_REVERSE_PIN, OUTPUT);
}

void FrankiAction::sampleFloor() {

    int blackReading = 0;
    int sampleCount = 100;

    for (int i = 0; i < sampleCount; i++)
    {
        int leftValue = _robotState.getLineSensorLeft().getValue();
        int rightValue = _robotState.getLineSensorRight().getValue();

        int average = (leftValue + rightValue) / 2;          
        blackReading += average;

        delay(5);
    }

    blackReading /= sampleCount;            
    _robotState.getLineSensorLeft().setBlackReading(blackReading);
    _robotState.getLineSensorRight().setBlackReading(blackReading);
}    

void FrankiAction::printValuesAnalog(u_int8_t pin) {
    while (true)
    {
        Serial.print("Analog value: ");
        Serial.println(analogRead(pin));
    }
}

void FrankiAction::printValuesDigital(u_int8_t pin) {
    while (true)
    {
        Serial.print("Digital value: ");
        Serial.println(digitalRead(pin));
    }
}




// motor control

void FrankiAction::stop() {
    analogWrite(PIN_MOTOR_LEFT_FORWARD_PIN, 255);
    analogWrite(PIN_MOTOR_LEFT_REVERSE_PIN, 255);
    analogWrite(PIN_MOTOR_RIGHT_FORWARD_PIN, 255);
    analogWrite(PIN_MOTOR_RIGHT_REVERSE_PIN, 255);
}


void FrankiAction::fullFowards() {
  analogWrite(PIN_MOTOR_LEFT_FORWARD_PIN, 255);
  analogWrite(PIN_MOTOR_LEFT_REVERSE_PIN, 0);
  analogWrite(PIN_MOTOR_RIGHT_FORWARD_PIN, 255);
  analogWrite(PIN_MOTOR_RIGHT_REVERSE_PIN, 0);
}


void FrankiAction::slowerForwards() {
  analogWrite(PIN_MOTOR_LEFT_FORWARD_PIN, 90);
  analogWrite(PIN_MOTOR_LEFT_REVERSE_PIN, 0);
  analogWrite(PIN_MOTOR_RIGHT_FORWARD_PIN, 90);
  analogWrite(PIN_MOTOR_RIGHT_REVERSE_PIN, 0);
}

void FrankiAction::boundaryDetectedTurn() {

    analogWrite(PIN_MOTOR_LEFT_FORWARD_PIN, 255);
    analogWrite(PIN_MOTOR_LEFT_REVERSE_PIN, 0);
    analogWrite(PIN_MOTOR_RIGHT_FORWARD_PIN, 0);
    analogWrite(PIN_MOTOR_RIGHT_REVERSE_PIN, 255);

    delay(150);

    stop();
}

void FrankiAction::moveBackwards() {

    analogWrite(PIN_MOTOR_LEFT_FORWARD_PIN, 0);
    analogWrite(PIN_MOTOR_LEFT_REVERSE_PIN, 255);
    analogWrite(PIN_MOTOR_RIGHT_FORWARD_PIN, 0);
    analogWrite(PIN_MOTOR_RIGHT_REVERSE_PIN, 255);

    delay(200);

    stop();
}


void FrankiAction::detectionManeuver() {
    moveBackwards();
    boundaryDetectedTurn();
}

void FrankiAction::search() {
    if (_robotState.isAtBounds())
    {
        detectionManeuver();
    } else {
        slowerForwards();
    }
}


void FrankiAction::slightRight() {
            analogWrite(PIN_MOTOR_LEFT_FORWARD_PIN, 35);
            analogWrite(PIN_MOTOR_LEFT_REVERSE_PIN, 0);
            analogWrite(PIN_MOTOR_RIGHT_FORWARD_PIN, 0);
            analogWrite(PIN_MOTOR_RIGHT_REVERSE_PIN, 35);
}

void FrankiAction::slightLeft() {
            analogWrite(PIN_MOTOR_LEFT_FORWARD_PIN, 0);
            analogWrite(PIN_MOTOR_LEFT_REVERSE_PIN,35);
            analogWrite(PIN_MOTOR_RIGHT_FORWARD_PIN, 35);
            analogWrite(PIN_MOTOR_RIGHT_REVERSE_PIN, 0);
}

void FrankiAction::right() {
                  analogWrite(PIN_MOTOR_LEFT_FORWARD_PIN, 75);
              analogWrite(PIN_MOTOR_LEFT_REVERSE_PIN, 0);
              analogWrite(PIN_MOTOR_RIGHT_FORWARD_PIN, 0);
              analogWrite(PIN_MOTOR_RIGHT_REVERSE_PIN, 75);
}

void FrankiAction::left() {
                  analogWrite(PIN_MOTOR_LEFT_FORWARD_PIN, 0);
              analogWrite(PIN_MOTOR_LEFT_REVERSE_PIN, 75);
              analogWrite(PIN_MOTOR_RIGHT_FORWARD_PIN, 75);
              analogWrite(PIN_MOTOR_RIGHT_REVERSE_PIN, 0);
}



void FrankiAction::sharpRight() {
        analogWrite(PIN_MOTOR_LEFT_FORWARD_PIN, 255);
    analogWrite(PIN_MOTOR_LEFT_REVERSE_PIN, 0);
    analogWrite(PIN_MOTOR_RIGHT_FORWARD_PIN, 0);
    analogWrite(PIN_MOTOR_RIGHT_REVERSE_PIN, 255);
    
    delay(150);
    
    stop();

}

void FrankiAction::sharpLeft() {
      analogWrite(PIN_MOTOR_LEFT_FORWARD_PIN, 0);
  analogWrite(PIN_MOTOR_LEFT_REVERSE_PIN, 255);
  analogWrite(PIN_MOTOR_RIGHT_FORWARD_PIN, 255);
  analogWrite(PIN_MOTOR_RIGHT_REVERSE_PIN, 0);

  delay(150);

  stop();
}