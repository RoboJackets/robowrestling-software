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
const byte backleft = A6;
const byte backright = A7;
const byte frontright = A2;
const byte frontleft = A3;

// Window size of the median filter (odd number, 1 = no filtering)
const byte mediumFilterWindowSize = 5;
unsigned int distance;
unsigned int distance2;

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
short iter;
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
  iter = 0;
  threshold = analogRead(backleft) - 200;
  distance = sensor.getDist();
  distance2 = sensor2.getDist();
}

void loop() {
  // Get distance from sensor
  iter ++;
  if (iter == 1) {
    distance = sensor.getDist();
    distance2 = sensor2.getDist();
    Serial.print(past);
    Serial.print(", ");
    Serial.print(distance);
    Serial.print(", ");
    Serial.print(distance2);
    Serial.print(", ");
    Serial.print(analogRead(backleft));
    Serial.print(", ");
    Serial.print(analogRead(backright));
    Serial.print(", ");
    Serial.print(analogRead(frontleft));
    Serial.print(", ");
    Serial.println(analogRead(frontright));
  } else if (iter == 5) {
    iter = 0;
  }
  if (analogRead(backleft) < threshold) {
    move(1, 120, 1); //motor 1, full speed, left
    move(2, 40, 0); //motor 2, full speed, left
    past = 'f';
    delay(50);
  } else if (analogRead(backright) < threshold) {
    move(1, 40, 1); //motor 1, full speed, left
    move(2, 120, 0); //motor 2, full speed, left
    past = 'f';
    delay(50);
  } else if (analogRead(frontleft) < threshold) {
    move(1, 40, 0); //motor 1, full speed, left
    move(2, 120, 1); //motor 2, full speed, left
    past = 'f';
    delay(50);
  } else if (analogRead(frontright) < threshold) {
    move(1, 120, 0); //motor 1, full speed, left
    move(2, 40, 1); //motor 2, full speed, left
    past = 'f';
    delay(50);
  } else if (iter == 1){
    if (((past == 'f' || count >= 100) && (distance > 600 && distance2 > 600)) || (distance <= 300 && distance2 <= 300) || (abs(distance - distance2) <= 150)) {
      move(1, 128, 1); //motor 1, full speed, left
      move(2, 128, 0); //motor 2, full speed, left
      past = 'f';
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
      count = 0;
    } else{
      move(1, 128, 1); //motor 1, full speed, left
      move(2, 20, 0); //motor 2, full speed, left
      past = 'r';
      count = 0;
    }
  }
  
  
  // Print distance to Serial
  // Wait some time
  delay(5);
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
