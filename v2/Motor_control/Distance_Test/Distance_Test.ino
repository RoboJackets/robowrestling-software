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
const byte sensorPin4 = A4; //A4: left peripheral sensor
const byte sensorPin3 = A5;//A5: right peripheral sensor

// Window size of the median filter (odd number, 1 = no filtering)
const byte mediumFilterWindowSize = 5;
unsigned int rightDist; //distance from right sensor
unsigned int leftDist; //distance from left sensor
unsigned int perRightDist; //distance from peripheral right sensor
unsigned int perLeftDist; //distance from peripheral left sensor

// Create an object instance of the SharpDistSensor class
SharpDistSensor sensor(sensorPin, mediumFilterWindowSize); //right sensor
SharpDistSensor sensor2(sensorPin2, mediumFilterWindowSize); //left sensor
SharpDistSensor sideright(sensorPin3, mediumFilterWindowSize); //right peripheral sensor
SharpDistSensor sideleft(sensorPin4, mediumFilterWindowSize); //left peripheral sensor
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
int curIR; // current time
int prevIR; 
int curLine; 
int prevLine; 
short iter;
int maxS;
int minS;
int buttonPushCounter;
int lastButtonState;
int buttonState;
int near = 200;
int far = 500;
int buttonPin = 2;
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
  prevLine = millis();
  prevIR = prevLine;
  setSpeed(128, 20);
  lastButtonState = digitalRead(buttonPin);
  buttonPushCounter = 0;
}

void loop() {
  curLine = millis();
  curIR = curLine;
  
  //print out values from sensors and motors to the console
  /*
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
  */
  Serial.print(buttonPushCounter);
  Serial.print(", ");
  Serial.println(curLine - prevLine);
  buttonState = digitalRead(buttonPin);

  // compare the buttonState to its previous state
  if (buttonState != lastButtonState) {
    // if the state has changed, increment the counter
    if (buttonState == HIGH) {
      // if the current state is HIGH then the button went from off to on:
      buttonPushCounter++;
      Serial.println("on");
      Serial.print("number of button pushes: ");
      Serial.println(buttonPushCounter);
    } else {
      // if the current state is LOW then the button went from on to off:
      Serial.println("off");
    }
    // Delay a little bit to avoid bouncing
    delay(50);
  }
  // save the current state as the last state, for next time through the loop
  lastButtonState = buttonState;

  if ((curLine - prevLine) >= 5) {
    prevLine = curLine;
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
    } else if ((curIR - prevIR) >= 25){
      prevIR = curIR;
      // Get distance from sensors
      rightDist = sensor.getDist();
      leftDist = sensor2.getDist();
      perRightDist = sideright.getDist();
      perLeftDist = sideleft.getDist();
      if (perLeftDist <= near) {
        //if there is an object within nearmm of the left peripheral sensor, move left
        //turn left in place
        leftInPlace();
        past = 'l'; //set past movement to left
        count = 0; //reset abandon search count because the robot has found an object
      } else if (perRightDist <= near) {
        //if there is an object within nearmm of the right peripheral sensor, move right
        //turn right in place
        rightInPlace();
        past = 'r'; //set past movement to left
        count = 0; //reset abandon search count because the robot has found an object
      } else if (((past == 'f' || count >= 100) && (rightDist > far && leftDist > far && perRightDist > far && perLeftDist > far)) 
            || (rightDist <= near && leftDist <= near) 
            || (abs(rightDist - leftDist) <= 150)) {
        //if (robot moved forward in the past OR it's been searching for 100 iterations) AND (there isn't an object within far of any IR sensor))
        //OR there is an object within near of both sensors 
        //OR the difference between the two distances measured by the IR sensors is within 150mm of each other
        //move forward
        forward();
        past = 'f'; //set past movement to forward
        count = 0; //reset abandon search count
      } else if (past == 'l' && (rightDist > far && leftDist > far && perRightDist > far && perLeftDist > far)) {
        //if robot has been moving left in the past, move left more
        left();
        past = 'l'; //set past movement to left
        count++; //increment abandon search count
      } else if (past == 'r' && (rightDist > far && leftDist > far && perRightDist > far && perLeftDist > far)) {
        //if robot has been moving right in the past, move right
        right();
        past = 'r'; //set past movement to right
        count++; //increment abandon search count
      } else if (rightDist <= far || perRightDist <= far) {
        //if there is an object beyond farmm of the left sensors (i.e. there is something closer in the right sensors), move right
        right();
        past = 'r'; //set past movement to right
        count = 0; //reset abandon search count because the robot has found an object
      } else if (leftDist <= far || perLeftDist <= far) {
        //if there is an object beyond farmm of the right sensors (i.e. there is something closer in the left sensors), move left
        left();
        past = 'l'; //set past movement to left
        count = 0; //reset abandon search count because the robot has found an object
      }
    }
  }
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

void forward() {
  move(1, maxS, 1); //motor 1, full speed, left
  move(2, maxS, 0); //motor 2, full speed, left
}

void left() {
  move(1, minS, 1); //motor 1, full speed, left
  move(2, maxS, 0); //motor 2, full speed, left
}

void right() {
  move(1, maxS, 1); //motor 1, full speed, left
  move(2, minS, 0); //motor 2, full speed, left
}

void leftInPlace() {
  move(1, maxS, 0); //motor 1, full speed, left
  move(2, maxS, 0); //motor 2, full speed, left
}

void rightInPlace() {
  move(1, maxS, 1); //motor 1, full speed, left
  move(2, maxS, 1); //motor 2, full speed, left
}

void setSpeed(int ma, int mi) {
  maxS = ma;
  minS = mi;
}

