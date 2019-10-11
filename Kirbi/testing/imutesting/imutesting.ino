#include "Wire.h"

void setup() {
  // put your setup code here, to run once:
  pinMode(9, OUTPUT);
  digitalWrite(9, LOW);
  Serial.begin(115200);
  //Wire with SDA 8 and SCL 7 for Kirbi. Wire2 with SDA 4 and SCL3
  Wire.begin();
  Wire.setSDA(8);
  Wire.setSCL(7);
}

void loop() {
  // put your main code here, to run repeatedly:
  Serial.print("Result:");
  Wire.beginTransmission(0x68);
  Wire.write(0);
  Wire.endTransmission();
  Wire.requestFrom(0x68, (byte)1);
  Serial.println(Wire.read());
  Wire.endTransmission();
  delay(100);
}
