/*
SharpDistSensorBasic.ino
Source: https://github.com/DrGFreeman/SharpDistSensor
MIT License
Copyright (c) 2017 Julien de la Bruere-Terreault <drgfreeman@tuta.io>
Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:
The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.
THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

/*
This example shows how to use the SharpDistSensor library to continuously
read the sensor and display the analog value and the corrseponding distance
in mm.
The library default values corresponding to the Sharp GP2Y0A60SZLF 5V sensor
are used.
See the library README for how to use pre-defined sensor models or custom
fit functions.
*/

#include <SharpDistSensor.h>

// Analog pin to which the sensor is connected
const byte sensorPin = A0;
const byte sensorPin2 = A1;
const byte backleft = A2;
const byte backright = A3;
const byte frontright = A4;
const byte frontleft = A5;

// Window size of the median filter (odd number, 1 = no filtering)
const byte mediumFilterWindowSize = 5;

// Create an object instance of the SharpDistSensor class
SharpDistSensor sensor(sensorPin, mediumFilterWindowSize);
SharpDistSensor sensor2(sensorPin2, mediumFilterWindowSize);
int STBY = 10; //standby

//Motor A
int PWMA = 3; //Speed control
int AIN1 = 9; //Direction
int AIN2 = 8; //Direction

//Motor B
int PWMB = 5; //Speed control
int BIN1 = 11; //Direction
int BIN2 = 12; //Direction
char past;
int count;
int threshold;
void setup() {
  Serial.begin(9600);
  pinMode(STBY, OUTPUT);

  pinMode(PWMA, OUTPUT);
  pinMode(AIN1, OUTPUT);
  pinMode(AIN2, OUTPUT);
  
  pinMode(PWMB, OUTPUT);
  pinMode(BIN1, OUTPUT);
  pinMode(BIN2, OUTPUT);
  past = 'f';
  count = 0;
  threshold = analogRead(backleft) + 200;
}

void loop() {
  // Get distance from sensor
  unsigned int distance = sensor.getDist();
  unsigned int distance2 = sensor2.getDist();
  if (backleft > threshold) {
    move(1, 120, 1); //motor 1, full speed, left
    move(2, 40, 0); //motor 2, full speed, left
  } else if (backright > threshold) {
    move(1, 40, 1); //motor 1, full speed, left
    move(2, 120, 0); //motor 2, full speed, left
  } else if (frontleft > threshold) {
    move(1, 40, 0); //motor 1, full speed, left
    move(2, 120, 1); //motor 2, full speed, left
  } else if (frontright > threshold) {
    move(1, 120, 0); //motor 1, full speed, left
    move(2, 40, 1); //motor 2, full speed, left
  } else if (((past == 'f' || count >= 30) && (distance > 600 && distance2 > 600)) || (distance <= 300 && distance2 < 300)) {
    move(1, 128, 1); //motor 1, full speed, left
    move(2, 128, 0); //motor 2, full speed, left
    past == 'f';
    count = 0;
  } else if (past == 'l') {
    move(1, 20, 1); //motor 1, full speed, left
    move(2, 128, 0); //motor 2, full speed, left
    past = 'l';
    count++;
  } else if (past == 'r') {
    move(1, 128, 1); //motor 1, full speed, left
    move(2, 20, 0); //motor 2, full speed, left
    past = 'r';
    count++;
  } else if (distance > 600) {
    move(1, 20, 1); //motor 1, full speed, left
    move(2, 128, 0); //motor 2, full speed, left
    past = 'l';
  } else{
    move(1, 128, 1); //motor 1, full speed, left
    move(2, 20, 0); //motor 2, full speed, left
    past == 'r';
  }
  

  // Print distance to Serial
  Serial.println(distance/25.4);

  // Wait some time
  delay(30);
}

void move(int motor, int speed, int direction){
//Move specific motor at speed and direction
//motor: 0 for B 1 for A
//speed: 0 is off, and 255 is full speed
//direction: 0 clockwise, 1 counter-clockwise

digitalWrite(STBY, HIGH); //disable standby

boolean inPin1 = LOW;
boolean inPin2 = HIGH;

if(direction == 1){
inPin1 = HIGH;
inPin2 = LOW;
}

if(motor == 1){
digitalWrite(AIN1, inPin1);
digitalWrite(AIN2, inPin2);
analogWrite(PWMA, speed);
}else{
digitalWrite(BIN1, inPin1);
digitalWrite(BIN2, inPin2);
analogWrite(PWMB, speed);
}
}

void stop(){
//enable standby
digitalWrite(STBY, LOW);
}

