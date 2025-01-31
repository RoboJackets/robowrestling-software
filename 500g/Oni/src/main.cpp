#include <Arduino.h>
#include "state/sensors/irsensor.h"
#include "state/sensors/linesensor.h"

LINESENSOR left_line(A0); // A0
LINESENSOR right_line(A1); // A1


void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  Serial.println(left_line.getValue());
  delay(10);
}

