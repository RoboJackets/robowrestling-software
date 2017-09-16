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
const byte sensorPin = A0; //right IR sensor
const byte sensorPin2 = A1; //left IR sensor
const byte backleft = A6; //back-left line sensor
const byte backright = A7; //back-right line sensor
const byte frontright = A2; //front-left line sensor
const byte frontleft = A3; //front-right line sensor
const byte sideleft = A4; //A4: left peripheral sensor
const byte sideright = A5;//A5: right peripheral sensor

// Window size of the median filter (odd number, 1 = no filtering)
const byte mediumFilterWindowSize = 5;
unsigned int rightDist; //distance from right sensor
unsigned int leftDist; //distance from left sensor
unsigned int perRightDist; //distance from peripheral right sensor
unsigned int perLeftDist; //distance from peripheral left sensor

// Create an object instance of the SharpDistSensor class
SharpDistSensor sensor(sensorPin, mediumFilterWindowSize); //right sensor
SharpDistSensor sensor2(sensorPin2, mediumFilterWindowSize); //left sensor
int STBY = 10; //standby

//Right Motor (? I'm not too sure about this)
int PWMA = 3; //Speed control
int AIN1 = 9; //Direction
int AIN2 = 8; //Direction

//Left Motor (? also not too sure about this)
int PWMB = 5; //Speed control
int BIN1 = 11; //Direction
int BIN2 = 12; //Direction
char past; //what direction the robot was moving previously
int count; //counter for how long before the rebot gives up searching in one direction
int threshold; //threshold for line sensors
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

  //initialising values
  past = 'f'; //set default move to forward
  count = 0;
  iter = 0;
  threshold = analogRead(backleft) - 200;
  rightDist = sensor.getDist();
  leftDist = sensor2.getDist();
  perRightDist = sideright.getDist();
  perLeftDist = sideleft.getDist();
}

void loop() {
  // Get distance from sensor
  iter++;
  if (iter == 1) {
    //print out values from sensors and motors to the console
    rightDist = sensor.getDist();
    leftDist = sensor2.getDist();
    perRightDist = sideright.getDist();
    perLeftDist = sideleft.getDist();
    Serial.print(past);
    Serial.print(", ");
    Serial.print(rightDist);
    Serial.print(", ");
    Serial.print(leftDist);
    Serial.print(", ");
    Serial.print(perRightDist);
    Serial.print(", ");
    Serial.print(perLeftDist);
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
  if (analogRead(backleft) < threshold) { //first read from line sensors before doing anything else
    //if line detected by back-left line sensor, turn left a bit
    move(1, 40, 1); //motor 1, full speed, left
    move(2, 120, 0); //motor 2, full speed, left
    past = 'f'; //set default move to forward
    delay(50); //wait 50ms for the IR sensors to take new reading
  } else if (analogRead(backright) < threshold) {
    //if line detected by back-right line sensor, turn right a bit
    move(1, 120, 1); //motor 1, full speed, left
    move(2, 40, 0); //motor 2, full speed, left
    past = 'f';
    delay(50);
  } else if (analogRead(frontleft) < threshold) {
    //if line dectected by front-left sensor, go back and to the left a bit
    move(1, 40, 0); //motor 1, full speed, left
    move(2, 120, 1); //motor 2, full speed, left
    past = 'f';
    delay(50);
  } else if (analogRead(frontright) < threshold) {
    //if line detected by front-right sensor, go back and to the right a bit
    move(1, 120, 0); //motor 1, full speed, left
    move(2, 40, 1); //motor 2, full speed, left
    past = 'f';
    delay(50);
  } else if (iter == 1){
    if (((past == 'f' || count >= 100) && (rightDist > 600 && leftDist > 600 && perRightDist > 600 && perLeftDist > 600)) 
          || (rightDist <= 300 && leftDist <= 300) 
          || (abs(rightDist - leftDist) <= 150)) {
      //if (robot moved forward in the past OR it's been searching for 100 iterations) AND (there isn't an object within 600mm of any IR sensor))
      //OR there is an object within 300mm of both sensors 
      //OR the difference between the two distances measured by the IR sensors is within 150mm of each other
      //move forward
      move(1, 128, 1); //motor 1, full speed, left
      move(2, 128, 0); //motor 2, full speed, left
      past = 'f'; //set past movement to forward
      count = 0; //reset abandon search count
    } else if (past == 'l') {
      //if robot has been moving left in the past, move left more
      move(1, 20, 1); //motor 1, full speed, left
      move(2, 128, 0); //motor 2, full speed, left
      past = 'l'; //set past movement to left
      count++; //increment abandon search count
    } else if (past == 'r') {
      //if robot has been moving right in the past, move right
      move(1, 128, 1); //motor 1, full speed, left
      move(2, 20, 0); //motor 2, full speed, left
      past = 'r'; //set past movement to right
      count++; //increment abandon search count
    } else if (rightDist > 600) {
      //if there is an object beyond 600mm of the right sensors (i.e. there is something closer in the left sensors), move left
      move(1, 20, 1); //motor 1, full speed, left
      move(2, 128, 0); //motor 2, full speed, left
      past = 'l'; //set past movement to left
      count = 0; //reset abandon search count because the robot has found an object
    } else {
      //else (i.e. there is an object closer in the right sensor), move right
      move(1, 128, 1); //motor 1, full speed, left
      move(2, 20, 0); //motor 2, full speed, left
      past = 'r'; //set past movement to right
      count = 0; //reset abandon search count
    }
  }
  
  // Print distance to Serial
  // Wait some time
  delay(5);
}

void move(int motor, int speed, int direction){
  //Move specific motor at speed and direction
  //motor: 1 for right, 2 for left
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
  } else {
    digitalWrite(BIN1, inPin1);
    digitalWrite(BIN2, inPin2);
    analogWrite(PWMB, speed);
  }
}

void stop(){
  //enable standby
  digitalWrite(STBY, LOW);
}
