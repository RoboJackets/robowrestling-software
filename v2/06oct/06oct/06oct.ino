/*
Robojackets Robot Sumo Team Pushiv
Source: https://github.com/simplyellow/auto-sumo.git
Copyright (c) 2017 Georgia Tech Robojackets
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
const byte hallSensorR = 8;
const byte hallSensorL = 9;

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
int searchCount; //counter for how long before the rebot gives up searching in one direction
int attackCount; // counter for how long robot attacks for
int threshold; //threshold for line sensors
int prevIR; // past time IR sensors were polled
int cur; // current timer
int prevFlag; // timer for some movement
int prevLine; // past time line sensors were polled
int state; // movement state of robot
int rangeThresh; // also not sure about this
int lineFlag; // flag to mark if line has been met
boolean pivotFlag; // flag to mark if the robot has pivoted
boolean pastNear; // flag to mark if the opponent was near the robot last
int speedArrR[5]; //running average for calculating velocity
int speedArrL[5];
int expectedVelR; //expected velocity
int expectedVelL;
bool prevHallR; //if at previous measurement the hallsensor was on
bool prevHallL;
int arrPosR; //pointer to insert values in the speed array
int arrPosL;

// thresholds for distance sensors
int near = 200;
int far = 500;
int dist = 150;

// thresholds for movement timers
int degreesMin = 20; // turn a little
int degrees90 = 50; // turn 90 degrees
int degrees180 = 100; // turn 180 degrees
int startSpinR = 1000; // time spinning right at start
int startTurnL = 2000; // time turning left at start
int startSpinL = 1000; // time spinning left at start
int startCross = 500; // time crossing the arena
int pivotBack = 500; // time moving back at pivot
int pivotSpinR = 1000; // time spinning right at pivot
int pivotTurnL = 1000; // time turning left at pivot
int pivotSpinL = 1000; // time spinning left at pivot

// max and minimum motor speeds
int maxS = 128;
int minS = 20;

void setup() {
  Serial.begin(9600);
  pinMode(STBY, OUTPUT);

  pinMode(PWMA, OUTPUT);
  pinMode(AIN1, OUTPUT);
  pinMode(AIN2, OUTPUT);

  pinMode(PWMB, OUTPUT);
  pinMode(BIN1, OUTPUT);
  pinMode(BIN2, OUTPUT);

  pinMode(hallSensorR, INPUT);
  pinMode(hallSensorL, INPUT);
  //initialising values
  past = 'f'; //set default move to forward
  searchCount = 0;
  attackCount = 0;
  threshold = analogRead(backleft) - 200; // set start value for line sensors to compare
  rightDist = sensor.getDist(); // poll right sensor
  leftDist = sensor2.getDist(); // poll left sensor
  perRightDist = sideright.getDist(); // poll peripheral right sensor
  perLeftDist = sideleft.getDist(); // poll peripheral left sensor
  prevLine = millis();
  prevIR = prevLine;
  lineFlag = 0;
  pivotFlag = true;
  pastNear = false;
  prevFlag = prevLine;
  speedArrR = {prevLine, prevLine, prevLine, prevLine, prevLine};
  speedArrL = {prevLine, prevLine, prevLine, prevLine, prevLine};
  arrPosR = 0;
  arrPosL = 0.
  prevHallR = false;
  prevHallL = false;
  state = 11; // at start, movement state is the startup state
}

void loop() {
  cur = millis();
  if (digitalRead(hallSensorR), HIGH) {
    if {!prevHallR) {
      prevHallR = true;
      speedArrR[arrPosR % 5] = cur;
      arrPosR++;
    } else {
      prevHallR = false;
    }
  }
  if (digitalRead(hallSensorL), HIGH) {
    if {!prevHallL) {
      prevHallL = true;
      speedArrL[arrPosL % 5] = cur;
      arrPosL++;
    } else {
      prevHallL = false;
    }
  }
  movement(state);
//  perLeftDist += 350;

  //print out values from sensors and motors to the console
  Serial.print(past);
  Serial.print(", ");
  Serial.print(state);
  Serial.print(", ");
  Serial.print(searchCount);
  Serial.print(", ");
  Serial.print(rightDist);
  Serial.print(", ");
  Serial.print(leftDist);
  Serial.print(", ");
  Serial.print(perRightDist);
  Serial.print(", ");
  Serial.println(perLeftDist);
//  Serial.print(", ");
//  Serial.print(analogRead(backleft));
//  Serial.print(", ");
//  Serial.print(analogRead(backright));
//  Serial.print(", ");
//  Serial.print(analogRead(frontleft));
//  Serial.print(", ");
//  Serial.println(analogRead(frontright));
//  Serial.print(", ");
//  Serial.println(cur - prevLine);

  if ((cur - prevLine) >= 5) {
    prevLine = cur;
    if ((analogRead(backleft) < threshold || analogRead(backright) < threshold) && lineFlag != 1) {
      //if line detected by back line sensors and wasn't detected before, go forward
      state = 0;
      lineFlag = 1; // set line flag state
      prevFlag = cur;
      pivotFlag = false;
      pastNear = false;
    } else if (analogRead(frontleft) < threshold && past == 'l' && lineFlag != 2) {
      // if past left and front left hits line and wasn't hit before, turn back right, spin left
      state = 6;
      lineFlag = 2; // set line flag state
      prevFlag = cur;
      pivotFlag = false;
      pastNear = false;
    } else if (analogRead(frontleft) < threshold && past == 'r' || analogRead(frontleft) < threshold && past == 'f' && lineFlag != 3) {
      // if past right or forward and front left hits line and wasn't hit before, turn back right, spin right
      state = 7;
      lineFlag = 3; // set line flag state
      prevFlag = cur;
      pivotFlag = false;
      pastNear = false;
    } else if (analogRead(frontright) < threshold && past == 'l' && lineFlag != 4) {
      // if past left and front right hits line and wasn't hit before, turn back left, spin right
      state = 8;
      lineFlag = 4; // set line flag state
      prevFlag = cur;
      pivotFlag = false;
      pastNear = false;
    } else if (analogRead(frontright) < threshold && past == 'r' || analogRead(frontright) < threshold && past == 'f' && lineFlag != 5) {
      // if past right or forward and front right hits line and wasn't hit before, turn back left, spin left
      state = 9;
      lineFlag = 5; // set line flag state
      prevFlag = cur;
      pivotFlag = false;
      pastNear = false;
    } else if (analogRead(frontright) < threshold && analogRead(frontleft) < threshold && lineFlag != 6) {
      // if both front corners hits line and wasn't hit before, go back and spin 180 degrees
      state = 10;
      lineFlag = 6; // set line flag state
      prevFlag = cur;
      pivotFlag = false;
      pastNear = false;
    } else if ((cur - prevIR) >= 25) {
      // otherwise, poll all the distance sensors
      prevIR = cur;
      rightDist = sensor.getDist();
      leftDist = sensor2.getDist();
      perRightDist = sideright.getDist();
      perLeftDist = sideleft.getDist();

      //attack code with sensors

      if (!pivotFlag) { // first check if the robot hasn't pivoted in the past (if it has, don't do any of the actions below)
        if (past == 'f' && pastNear && attackCount < 100) {
          // if past forward, opponent used to be close to the front, and attack timer hasn't run out, full speed ahead
          past = 'f';
          state = 1;
          attackCount++; // increment attack counter
          pastNear = true;
        } else if (past == 'f' && pastNear && attackCount > 100) {
          // if past forward, opponent used to be close to the front, and the attack timer ran out, normal speed forward
          past = 'f';
          attackCount = 0; // clear attack counter
          state = 0;
          pastNear = true;
        } // hall sensor attack code

        else if (perLeftDist <= near) {
          //if opponent within near of the left peripheral sensor, spin left
          state = 4;
          past = 'l'; // set past movement to left
          searchCount = 0; // reset abandon search count because the robot has found an object
          attackCount = 0;
          pastNear = false;
        } else if (perRightDist <= near) {
          //if opponent within near of the right peripheral sensor, spin right
          state = 5;
          past = 'r'; //set past movement to left
          searchCount = 0; //reset abandon search count because the robot has found an object
          pastNear = false;
          attackCount = 0;
        } else if ((perRightDist <= near && perLeftDist <= near) || (rightDist <= near && leftDist <= near)) {
          //if there is an object within near of both peripheral sensors or within near of both middle sensors, move forward
          state = 0;
          past = 'f'; //set past movement to left
          searchCount = 0; //reset abandon search count because the robot has found an object
          pastNear = true; // opponent was near in the past
          attackCount = 0;
        } else if (lineFlag == 0) {
          if ((abs(rightDist - leftDist) <= 150)
                || ((past == 'f' || searchCount >= 100) && (rightDist > far && leftDist > far && perRightDist > far && perLeftDist > far))) {
            //if (robot moved forward in the past OR it's been searching for 100 iterations) AND (there isn't an object within far of any IR sensor))
            //move forward
            state = 0;
            past = 'f'; //set past movement to forward
            searchCount = 0; //reset abandon search count
            pastNear = false;
            attackCount = 0;
          } else if ((leftDist <= far || perLeftDist <= far)) { // || leftDist - rightDist < -dist) {
            // if opponent within far of the left sensors or if difference within some negative threshold, move left
            state = 2;
            past = 'l'; //set past movement to left
            searchCount = 0; //reset abandon search count because the robot has found an object
            pastNear = false;
            attackCount = 0;
          } else if ((rightDist <= far || perRightDist <= far)) { // || leftDist - rightDist > dist) {
            //if opponent within far of the right sensors or if difference within some positive threshold, move right
            state = 3;
            past = 'r'; //set past movement to right
            searchCount = 0; //reset abandon search count because the robot has found an object
            pastNear = false;
            attackCount = 0;
          } else if (past == 'l') {
            //if robot has been moving left in the past, move left more
            state = 2;
            past = 'l'; //set past movement to left
            searchCount++; //increment abandon search count
            pastNear = false;
            attackCount = 0;
          } else if (past == 'r') {
            //if robot has been moving right in the past, move right
            state = 3;
            past = 'r'; //set past movement to right
            searchCount++; //increment abandon search count
            pastNear = false;
            attackCount = 0;
          }
        }
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
      move(1, maxS, 1);
      move(2, maxS, 0);
      break;
    case 1: //attack
      move(1, 255, 1);
      move(2, 255, 0);
      break;
    case 2: //left
      move(1, minS, 1);
      move(2, maxS, 0);
      break;
    case 3: //right
      move(1, maxS, 1);
      move(2, minS, 0);
      break;
    case 4: //left in place
      move(1, maxS, 0); 
      move(2, maxS, 0); 
      break;
    case 5: //right in place
      move(1, maxS, 1); 
      move(2, maxS, 1);
      break;
    case 6: //back right and left
      if (cur - prevFlag < degreesMin) {
        move(1, maxS, 0); 
        move(2, minS, 1);
      } else if (cur - prevFlag < degrees90) {
        move(1, maxS, 0); 
        move(2, maxS, 0);
      } else {
        lineFlag = 0;
      }
      break;
    case 7: //back right and right
      if (cur - prevFlag < degreesMin) {
        move(1, maxS, 0);
        move(2, minS, 1);
      } else if (cur - prevFlag < degrees90) {
        move(1, maxS, 1);
        move(2, maxS, 1);
      } else {
        lineFlag = 0;
      }
      break;
    case 8: //back left and right
      if (cur - prevFlag < degreesMin) {
        move(1, minS, 0);
        move(2, maxS, 1); 
      } else if (cur - prevFlag < degrees90) {
        move(1, maxS, 1); 
        move(2, maxS, 1);
      } else {
        lineFlag = 0;
      }
      break;
    case 9: //back left and left
      if (cur - prevFlag < degreesMin) {
        move(1, minS, 0); 
        move(2, maxS, 1); 
      } else if (cur - prevFlag < degrees90) {
        move(1, maxS, 0);
        move(2, maxS, 0);
      } else {
        lineFlag = 0;
      }
      break;
    case 10: //back and spin 180
      if (cur - prevFlag < degreesMin) {
        move(1, maxS, 0); 
        move(2, maxS, 0);
      } else if (cur - prevFlag < degrees180) {
        move(1, maxS, 0);
        move(2, maxS, 0);
      } else {
        lineFlag = 0;
      }
      break;
    case 11: //startup movement: spin right, turn left, spin left, go forward
      if (cur - prevFlag < startSpinR) {
        move(1, maxS, 1);
        move(2, maxS, 1);
      } else if (cur - prevFlag < startTurnL) {
        move(1, minS, 1);
        move(2, maxS, 0);
      } else if (cur - prevFlag < startSpinL) {
        move(1, maxS, 0); 
        move(2, maxS, 0); 
      } else {
        past = 'f';
        pivotFlag = false;
      }
      break;
    case 12: //pivot: go back, spin right, turn left, spin left, go forward
      if (cur - prevFlag < pivotBack) {
        move(1, maxS, 0);
        move(2, maxS, 0); 
      } else if (cur - prevFlag < pivotSpinR) {
        move(1, maxS, 1);
        move(2, maxS, 1);
      } else if (cur - prevFlag < pivotTurnL) {
        move(1, minS, 1);
        move(2, maxS, 0);
      } else if (cur - prevFlag < pivotSpinL) {
        move(1, maxS, 0);
        move(2, maxS, 0);
      } else {
        past = 'f';
        pivotFlag = false;
      }
      break;
  }
}

int getVelR() {
  int sum = 0;
  for(int i = 0; i < 4; i++) {
    sum += speedArrR[(i + arrPosR + 1) % 5] - speedArrR[(i + arrPosR) % 5];    
  }
  return sum/4;
}

int getVelL() {
  int sum = 0;
  for(int i = 0; i < 4; i++) {
    sum += speedArrL[(i + arrPosL + 1) % 5] - speedArrL[(i + arrPosL) % 5];    
  }
  return sum/4;
}
}
}

