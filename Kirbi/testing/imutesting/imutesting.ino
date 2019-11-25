#include "Wire.h"
#include "ICM20948.h"

ICM20948 icm(Wire2, (uint8_t)0x68);

void setup() {
  // put your setup code here, to run once:
  pinMode(9, OUTPUT);
  digitalWrite(9, LOW);
  Serial.begin(115200);
  //Wire with SDA 8 and SCL 7 for Kirbi. Wire2 with SDA 4 and SCL3
  Wire2.begin();
  Wire2.setSDA(4);
  Wire2.setSCL(3);
  Serial.print(icm.begin());
  icm.disableDataReadyInterrupt();
  icm.configAccel(ICM20948::ACCEL_RANGE_2G, ICM20948::ACCEL_DLPF_BANDWIDTH_6HZ);
  icm.configGyro(ICM20948::GYRO_RANGE_250DPS, ICM20948::GYRO_DLPF_BANDWIDTH_6HZ);
}

void loop() {
  // put your main code here, to run repeatedly:
  Serial.print("\nResult:");
  icm.readSensor();
  // Copied from BasicI2C example from library code
  Serial.print(icm.getAccelX_mss(),6);
  Serial.print("\t");
  Serial.print(icm.getAccelY_mss(),6);
  Serial.print("\t");
  Serial.print(icm.getAccelZ_mss(),6);
  Serial.print("\t");
  Serial.print(icm.getGyroX_rads(),6);
  Serial.print("\t");
  Serial.print(icm.getGyroY_rads(),6);
  Serial.print("\t");
  Serial.print(icm.getGyroZ_rads(),6);

  delay(100);
}
