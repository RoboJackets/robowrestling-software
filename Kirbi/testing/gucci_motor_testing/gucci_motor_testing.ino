#define ESC_L_SERIAL Serial1
#define ESC_R_SERIAL Serial3

#define ESC_L_ADDRESS 0x80
#define ESC_R_ADDRESS 0x81



void setup() {
  // put your setup code here, to run once:
  ESC_L_SERIAL.begin(115200);
}

void loop() {
  unsigned int bytes[3];
  bytes[0] = ESC_L_ADDRESS;
  bytes[1] = 0; //0 is drive forward
  bytes[2] = 63; //drive motor at half speed
  unsigned int crc;
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
  ESC_L_SERIAL.write(crc);
  delay(100);
  
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
  ESC_L_SERIAL.write(crc);
  delay(100);
}
