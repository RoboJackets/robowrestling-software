#include <SharpDistSensor.h>
#define pin A2
SharpDistSensor IR(pin, 5); 

void setup() {
  Serial.begin(9600);
}

void loop() {
  Serial.println(IR.getDist());
  // expected output: 1400-1500 max distance
}
