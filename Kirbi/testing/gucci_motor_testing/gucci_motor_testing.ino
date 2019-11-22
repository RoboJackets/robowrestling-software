#define ESC_L_SERIAL Serial1
#define ESC_R_SERIAL Serial3

#define ESC_L_ADDRESS 0x80
#define ESC_R_ADDRESS 0x80
#include <cstdint>

int counter = 0;

void encoderISR() {
  counter++;
}

void setup() {
  // put your setup code here, to run once:
  ESC_R_SERIAL.begin(115200);
  ESC_R_SERIAL.setRX(7);
  ESC_R_SERIAL.setTX(8);
  pinMode(A19, INPUT);
  attachInterrupt(A19, encoderISR, RISING);
}

void loop() {
  uint8_t bytes[3];
  bytes[0] = ESC_R_ADDRESS;
  bytes[1] = 0; //0 is drive forward
  bytes[2] = 63; //drive motor at half speed
  uint32_t crc = 0;
  for(int i = 0; i < 3; i++) {
    crc = crc ^ (bytes[i] << 8);
    for (int j = 0; j < 8; j++) {
      if (crc & 0x8000) {
        crc = (crc << 1) ^ 0x1021;
      } else {
        crc = crc << 1;
      }
    }
  }
  ESC_R_SERIAL.write(bytes[0]);
  ESC_R_SERIAL.write(bytes[1]);
  ESC_R_SERIAL.write(bytes[2]);
  ESC_R_SERIAL.write(((crc >> 8) & 0xFF));
  ESC_R_SERIAL.write((crc & 0xFF));
  Serial.println(counter);
  delay(100);
}
