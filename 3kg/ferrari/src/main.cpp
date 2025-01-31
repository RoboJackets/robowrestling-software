#include <Arduino.h>
#include "Sensors/IRSensor.h"

const int LS_RF1 = 15;
const int LS_RF2 = 14;
const int LS_PlowLeft = 16;
const int LS_PlowRight = 17;
const int LS_PlowMid = 20;
const int LS_BL1 = 41;
const int LS_BL2 = 40;
const int LS_LF2 = 27;
const int LS_LF1 = 26;
const int LS_BR1 = 21;
const int LS_BR2 = 23;
const int DS_90R = 0;
const int DS_60R = 1;
const int DS_60L = 28;
const int DS_90L = 29;
const int DS_45R = 3;
const int DS_FR = 2;
const int DS_MID = 10;
const int DS_45L = 12;
const int DS_FL = 11;
const int IMU_INT1 = 8;
const int IMU_INT2 = 7;
const int IMU_SDA = 18;
const int IMU_SCL = 19;
const int IMU_CS = 37;
const int LCD_SCL = 24;
const int LCD_SDA = 25;
const int StartMod = 33;
const int Button1 = 4;
const int MD_inputSignal1 = 38;
const int MD_inputSignal2 = 39;

IRSensor *irSensor;
IRSensor *lineSensor;

void pollSensors();
void debug();

void setup() {
    Serial.begin(9600);
    irSensor = new IRSensor[9];
    lineSensor = new IRSensor[11];
    pinMode(DS_90R, INPUT_PULLDOWN);
    pinMode(DS_60R, INPUT_PULLDOWN);
    pinMode(DS_45R, INPUT_PULLDOWN);
    pinMode(DS_FR, INPUT_PULLDOWN);
    pinMode(DS_MID, INPUT_PULLDOWN);
    pinMode(DS_90L, INPUT_PULLDOWN);
    pinMode(DS_60L, INPUT_PULLDOWN);
    pinMode(DS_45L, INPUT_PULLDOWN);
    pinMode(DS_FL, INPUT_PULLDOWN);
}

void loop() {
    pollSensors();
    debug();
}

void pollSensors() {
    irSensor[0].setValue(digitalRead(DS_90R));
    irSensor[1].setValue(digitalRead(DS_60R));
    irSensor[2].setValue(digitalRead(DS_45R));
    irSensor[3].setValue(digitalRead(DS_FR));
    irSensor[4].setValue(digitalRead(DS_MID));
    irSensor[5].setValue(digitalRead(DS_90L));
    irSensor[6].setValue(digitalRead(DS_60L));
    irSensor[7].setValue(digitalRead(DS_45L));
    irSensor[8].setValue(digitalRead(DS_FL));
}

void debug() {
    Serial.print(millis());
    Serial.print(": DS: ");
    for (int i = 0; i < 9; i++) {
        Serial.print(irSensor[i].getValue());
    }
    Serial.print(" RAW: ");
    Serial.print(digitalRead(DS_90R));
    Serial.print(digitalRead(DS_60R));
    Serial.print(digitalRead(DS_45R));
    Serial.print(digitalRead(DS_FR));
    Serial.print(digitalRead(DS_MID));
    Serial.print(digitalRead(DS_90L));
    Serial.print(digitalRead(DS_60L));
    Serial.print(digitalRead(DS_45L));
    Serial.print(digitalRead(DS_FL));
    Serial.println();
}
