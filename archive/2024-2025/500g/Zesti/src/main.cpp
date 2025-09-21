#include <Arduino.h>

#define LEFT_LINE_SENSOR_PIN 0
#define RIGHT_LINE_SENSOR_PIN 1
#define IR_SENSOR_PIN_1 A0
#define IR_SENSOR_PIN_2 A1
#define IR_SENSOR_PIN_3 A2
#define IR_SENSOR_PIN_4 A3
#define leftMotor 2
#define rightMotor 3

const int NUM_READINGS = 10;
const int REQUIRED_COUNT = 8;
const unsigned long READ_INTERVAL = 5;
int currentIndex = 0;
unsigned long lastReadTime = 0;

void setup() {
  Serial.begin(9600);
  pinMode(LEFT_LINE_SENSOR_PIN, INPUT);
  pinMode(RIGHT_LINE_SENSOR_PIN, INPUT);
  pinMode(IR_SENSOR_PIN_1, INPUT);
  pinMode(IR_SENSOR_PIN_2, INPUT);
  pinMode(IR_SENSOR_PIN_3, INPUT);
  pinMode(IR_SENSOR_PIN_4, INPUT);
  pinMode(leftMotor, OUTPUT);
  pinMode(rightMotor, OUTPUT);
}

void loop() {
  unsigned long currentTime = millis();

  if (currentTime - lastReadTime >= READ_INTERVAL) {
    lastReadTime = currentTime;
  }

  int leftLineSensorReading = digitalRead(LEFT_LINE_SENSOR_PIN);
  int rightLineSensorReading = digitalRead(RIGHT_LINE_SENSOR_PIN);
  int irSensorReading1 = analogRead(IR_SENSOR_PIN_1);
  int irSensorReading2 = analogRead(IR_SENSOR_PIN_2);
  int irSensorReading3 = analogRead(IR_SENSOR_PIN_3);
  int irSensorReading4 = analogRead(IR_SENSOR_PIN_4);

  leftLineReadings[currentIndex] = leftReading;
  rightLineReadings[currentIndex] = rightReading;

  if (leftLineSensorReading == 1 && rightLineSensorReading == 1) {
    analogWrite(leftMotor, 100);
    analogWrite(rightMotor, 100);
  } else if (leftLineSensorReading == 0 && rightLineSensorReading == 1) {
    analogWrite(leftMotor, 100);
    analoglWrite(rightMotor, 100);
  } else if (leftLineSensorReading == 1 && rightLineSensorReading == 0) {
    analogWrite(leftMotor, 100);
    analogWrite(rightMotor, 100);
  } else {
    analogWrite(leftMotor, 100);
    analogWrite(rightMotor, 100);
  }

  currentIndex = (currentIndex + 1) % NUM_READINGS;
}



// // put function declarations here:
// int myFunction(int, int);

// void setup() {
//   // put your setup code here, to run once:
//   int result = myFunction(2, 3);
// }

// void loop() {
//   // put your main code here, to run repeatedly:
// }

// // put function definitions here:
// int myFunction(int x, int y) {
//   return x + y;
// }