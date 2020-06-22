#define ESC_L_SERIAL Serial1
#define ESC_R_SERIAL Serial3

#define ESC_L_ADDRESS 0x80
#define ESC_R_ADDRESS 0x80
#include <cstdint>

int counter = 0;

bool go = true;

void encoderISR() {
  counter++;
}

void stop_motors() {
  go = false;
}

void setup() {
  // put your setup code here, to run once:
  ESC_R_SERIAL.begin(115200);
  ESC_R_SERIAL.setRX(7);
  ESC_R_SERIAL.setTX(8);
  ESC_L_SERIAL.begin(115200);
  ESC_L_SERIAL.setRX(27);
  ESC_L_SERIAL.setTX(26);
  pinMode(A19, INPUT);
  attachInterrupt(A19, encoderISR, RISING);
  pinMode(17, INPUT);
  pinMode(A22, OUTPUT);
  analogWrite(A22, 192);
  pinMode(18, INPUT);
  pinMode(19, INPUT);
  attachInterrupt(18, stop_motors, FALLING);
  attachInterrupt(19, stop_motors, FALLING);
}

void loop() {
  Serial.println(digitalRead(17));
  if (digitalRead(17)&&go) {
    Serial.println("go");
    uint8_t bytes[3];
    bytes[0] = ESC_R_ADDRESS;
    bytes[1] = 1; //0 is drive forward
    bytes[2] = 40; //drive motor at half speed
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
    bytes[0] = ESC_L_ADDRESS;
    bytes[1] = 0; //0 is drive forward
    bytes[2] = 40; //drive motor at half speed
    crc = 0;
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
    ESC_L_SERIAL.write(bytes[0]);
    ESC_L_SERIAL.write(bytes[1]);
    ESC_L_SERIAL.write(bytes[2]);
    ESC_L_SERIAL.write(((crc >> 8) & 0xFF));
    ESC_L_SERIAL.write((crc & 0xFF));
  } else {
    Serial.println("stop");
    uint8_t bytes[3];
    bytes[0] = ESC_R_ADDRESS;
    bytes[1] = 0; //0 is drive forward
    bytes[2] = 0; //drive motor at half speed
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
    bytes[0] = ESC_L_ADDRESS;
    bytes[1] = 0; //0 is drive forward
    bytes[2] = 0; //drive motor at half speed
    crc = 0;
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
    ESC_L_SERIAL.write(bytes[0]);
    ESC_L_SERIAL.write(bytes[1]);
    ESC_L_SERIAL.write(bytes[2]);
    ESC_L_SERIAL.write(((crc >> 8) & 0xFF));
    ESC_L_SERIAL.write((crc & 0xFF));
  }
}
