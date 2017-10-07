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
int rightDist; //distance from right sensor
int leftDist; //distance from left sensor
int perRightDist; //distance from peripheral right sensor
int perLeftDist; //distance from peripheral left sensor

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
int prevIR;
int cur;
int prevFlag;
int prevLine;
short iter;
int state;
int rangeThresh;
boolean start;
int lineFlag;
boolean pivotFlag;

int near = 200;
int far = 500;
int degreesMin = 20;
int degrees90 = 50;
int degrees180 = 100;
int dist = 150;
int maxS = 128;
int minS = 20;
int startSpinR = 1000;
int startTurnL = 2000;
int startSpinL = 1000;
int pivotBack = 500;
int pivotSpinR = 1000;
int pivotTurnL = 1000;
int pivotSpinL = 1000;

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
  start = true; //set startup flag
  count = 0;
  iter = 0;
  threshold = analogRead(backleft) - 200;
  rightDist = sensor.getDist();
  leftDist = sensor2.getDist();
  perRightDist = sideright.getDist();
  perLeftDist = sideleft.getDist();
  prevLine = millis();
  prevIR = prevLine;
  lineFlag = 0;
  pivotFlag = true;
  prevFlag = prevLine;
  state = 11;
}

void loop() {
  cur = millis();
  movement(state);

  //print out values from sensors and motors to the console
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
  Serial.print(", ");
  Serial.println(cur - prevLine);

  if ((cur - prevLine) >= 5) {
    prevLine = cur;
    if (analogRead(backleft) < threshold || analogRead(backright) < threshold && lineFlag != 1) { //first read from line sensors before doing anything else
      //if line detected by back line sensors, turn left a bit
      state = 0;
      lineFlag = 1;
      prevFlag = cur;
      pivotFlag = false;
    } else if (analogRead(frontleft) < threshold && past == 'l' && lineFlag != 2) {
      state = 6;
      lineFlag = 2;
      prevFlag = cur;
      pivotFlag = false;
    } else if (analogRead(frontleft) < threshold && past == 'r' || analogRead(frontleft) < threshold && past == 'f' && lineFlag != 3) {
      state = 7;
      lineFlag = 3;
      prevFlag = cur;
      pivotFlag = false;
    } else if (analogRead(frontright) < threshold && past == 'l' && lineFlag != 4) {
      state = 8;
      lineFlag = 4;
      prevFlag = cur;
      pivotFlag = false;
    } else if (analogRead(frontright) < threshold && past == 'r' || analogRead(frontright) < threshold && past == 'f' && lineFlag != 5) {
      state = 9;
      lineFlag = 5;
      prevFlag = cur;
      pivotFlag = false;
    } else if (analogRead(frontright) < threshold && analogRead(frontleft) < threshold && lineFlag != 6) {
      state = 10;
      lineFlag = 6;
      prevFlag = cur;
      pivotFlag = false;
    } else if ((cur - prevIR) >= 25) {
      prevIR = cur;
      // Get distance from sensors
      rightDist = sensor.getDist();
      leftDist = sensor2.getDist();
      perRightDist = sideright.getDist();
      perLeftDist = sideleft.getDist();

      //attack code with sensors

      if (!pivotFlag) {
        //other attack cases

        if (perLeftDist <= near) {
          //if there is an object within nearmm of the left peripheral sensor, move left
          //turn left in place
          state = 4;
          past = 'l'; //set past movement to left
          count = 0; //reset abandon search count because the robot has found an object
        } else if (perRightDist <= near) {
          //if there is an object within nearmm of the right peripheral sensor, move right
          //turn right in place
          state = 5;
          past = 'r'; //set past movement to left
          count = 0; //reset abandon search count because the robot has found an object
        } else if (perRightDist <= near && perLeftDist <= near) {
          //if there is an object within nearmm of both peripheral sensors, move forward
          state = 0;
          past = 'f'; //set past movement to left
          count = 0; //reset abandon search count because the robot has found an object
        } else if (lineFlag == 0) {
          if ((abs(rightDist - leftDist) <= 150)
                || ((past == 'f' || count >= 100) && (rightDist > far && leftDist > far && perRightDist > far && perLeftDist > far))) {
            //if (robot moved forward in the past OR it's been searching for 100 iterations) AND (there isn't an object within far of any IR sensor))
            //OR there is an object within near of both sensors
            //OR the difference between the two distances measured by the IR sensors is within 150mm of each other
            //move forward
            state = 0;
            past = 'f'; //set past movement to forward
            count = 0; //reset abandon search count
          } else if ((leftDist <= far || perLeftDist <= far) || leftDist - rightDist < -dist) {
            //if there is an object beyond farmm of the right sensors (i.e. there is something closer in the left sensors), move left
            state = 2;
            past = 'l'; //set past movement to left
            count = 0; //reset abandon search count because the robot has found an object
          } else if ((rightDist <= far || perRightDist <= far) || leftDist - rightDist > dist) {
            //if there is an object beyond farmm of the left sensors (i.e. there is something closer in the right sensors), move right
            state = 3;
            past = 'r'; //set past movement to right
            count = 0; //reset abandon search count because the robot has found an object
          } else if (past == 'l') {
            //if robot has been moving left in the past, move left more
            state = 2;
            past = 'l'; //set past movement to left
            count++; //increment abandon search count
          } else if (past == 'r') {
            //if robot has been moving right in the past, move right
            state = 3;
            past = 'r'; //set past movement to right
            count++; //increment abandon search count
          }
        }


//        } else if (past == 'l' && (rightDist > far && leftDist > far && perRightDist > far && perLeftDist > far)) {
//          //if robot has been moving left in the past, move left more
//          left();
//          past = 'l'; //set past movement to left
//          count++; //increment abandon search count
//        } else if (past == 'r' && (rightDist > far && leftDist > far && perRightDist > far && perLeftDist > far)) {
//          //if robot has been moving right in the past, move right
//          right();
//          past = 'r'; //set past movement to right
//          count++; //increment abandon search count
//        }
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

void movement(int state) {
  switch (state) {
    case 0: //forward
      move(1, maxS, 1); //right, full speed, counter clockwise
      move(2, maxS, 0); //left, full speed, clockwise
      break;
    case 1: //attack
      move(1, 255, 1); //right, full speed, counter clockwise
      move(2, 255, 0); //left, full speed, clockwise
      break;
    case 2: //left
      move(1, minS, 1); //right, min speed, counter clockwise
      move(2, maxS, 0); //left, full speed, clockwise
      break;
    case 3: //right
      move(1, maxS, 1); //right, full speed, counter clockwise
      move(2, minS, 0); //left, full speed, clockwise
      break;
    case 4: //left in place
      move(1, maxS, 0); //right, full speed, clockwise
      move(2, maxS, 0); //left, full speed, clockwise
      break;
    case 5: //right in place
      move(1, maxS, 1); //right, full speed, counter clockwise
      move(2, maxS, 1); //left, full speed, counter clockwise
      break;
    case 6: //back right and left
      if (cur - prevFlag < degreesMin) {
        move(1, maxS, 0); //right, full speed, counter clockwise
        move(2, minS, 1); //left, full speed, clockwise
      } else if (cur - prevFlag < degrees90) {
        move(1, maxS, 0); //right, full speed, clockwise
        move(2, maxS, 0); //left, full speed, clockwise
      } else {
        lineFlag = 0;
      }
      break;
    case 7: //back right and right
      if (cur - prevFlag < degreesMin) {
        move(1, maxS, 0); //right, full speed, counter clockwise
        move(2, minS, 1); //left, full speed, clockwise
      } else if (cur - prevFlag < degrees90) {
        move(1, maxS, 1); //right, full speed, counter clockwise
        move(2, maxS, 1); //left, full speed, counter clockwise
      } else {
        lineFlag = 0;
      }
      break;
    case 8: //back left and right
      if (cur - prevFlag < degreesMin) {
        move(1, minS, 0); //right, min speed, counter clockwise
        move(2, maxS, 1); //left, full speed, clockwise
      } else if (cur - prevFlag < degrees90) {
        move(1, maxS, 1); //right, full speed, counter clockwise
        move(2, maxS, 1); //left, full speed, counter clockwise
      } else {
        lineFlag = 0;
      }
      break;
    case 9: //back left and left
      if (cur - prevFlag < degreesMin) {
        move(1, minS, 0); //right, min speed, counter clockwise
        move(2, maxS, 1); //left, full speed, clockwise
      } else if (cur - prevFlag < degrees90) {
        move(1, maxS, 0); //right, full speed, clockwise
        move(2, maxS, 0); //left, full speed, clockwise
      } else {
        lineFlag = 0;
      }
      break;
    case 10: //back and spin 180
      if (cur - prevFlag < degreesMin) {
        move(1, maxS, 0); //right, full speed, clockwise
        move(2, maxS, 0); //left, full speed, clockwise
      } else if (cur - prevFlag < degrees180) {
        move(1, maxS, 0); //right, full speed, clockwise
        move(2, maxS, 0); //left, full speed, clockwise
      } else {
        lineFlag = 0;
      }
      break;
    case 11: //startup movement: spin right, turn left, spin left
      if (cur - prevFlag < startSpinR) {
        move(1, maxS, 1); //right, full speed, counter clockwise
        move(2, maxS, 1); //left, full speed, counter clockwise
      } else if (cur - prevFlag < startTurnL) {
        move(1, minS, 1); //right, min speed, counter clockwise
        move(2, maxS, 0); //left, full speed, clockwise
      } else if (cur - prevFlag < startSpinL) {
        move(1, maxS, 0); //right, full speed, clockwise
        move(2, maxS, 0); //left, full speed, clockwise
      } else {
        past = 'f';
        pivotFlag = false;
      }
      break;
    case 12: //pivot:
      if (cur - prevFlag < pivotBack) {
        move(1, maxS, 0); //right, full speed, clockwise
        move(2, maxS, 0); //left, full speed, clockwise
      } else if (cur - prevFlag < pivotSpinR) {
        move(1, maxS, 1); //right, full speed, counter clockwise
        move(2, maxS, 1); //left, full speed, counter clockwise
      } else if (cur - prevFlag < pivotTurnL) {
        move(1, minS, 1); //right, min speed, counter clockwise
        move(2, maxS, 0); //left, full speed, clockwise
      } else if (cur - prevFlag < pivotSpinL) {
        move(1, maxS, 0); //right, full speed, clockwise
        move(2, maxS, 0); //left, full speed, clockwise
      } else {
        past = 'f';
        pivotFlag = false;
      }
      break;
  }
}
