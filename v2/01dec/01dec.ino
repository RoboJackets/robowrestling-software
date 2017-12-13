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
#include <Servo.h>  // for ESCs

// Analog pin to which the sensor is connected
const byte BR = A3;           // back-right line sensor
const byte BL = A2;           // back-left line sensor
const byte FR = A1;           // front-right line sensor
const byte FL = A0;           // front-left line sensor

const byte LLO = A4;          // left-peripheral IR distance sensor
const byte LMO = A5;          // left-middle IR distance sensor
const byte RMO = A6;          // right-middle IR distance sensor
const byte RRO = A7;          // right-peripheral IR distance sensor

// const byte L_Hall = 2;        // left Hall sensor
// const byte R_Hall = 3;        // right Hall sensor
const byte startModule = 4;   // remote start module

// Window size of the median filter (odd number, 1 = no filtering)
const byte mediumFilterWindowSize = 5;

int rightDist;                //distance from right sensor
int leftDist;                 //distance from left sensor
int perRightDist;             //distance from peripheral right sensor
int perLeftDist;              //distance from peripheral left sensor

// Create an object instance of the SharpDistSensor class
SharpDistSensor rightMidIR(RMO, mediumFilterWindowSize);  // RMO
SharpDistSensor leftMidIR(LMO, mediumFilterWindowSize);   // LMO
SharpDistSensor rightPerIR(RRO, mediumFilterWindowSize);  // RRO
SharpDistSensor leftPerIR(LLO, mediumFilterWindowSize);   // LLO

Servo L_ESC;  //Left motor
Servo R_ESC;  //Right motor

char past;          //what direction the robot was moving previously
int searchCount;    //counter for how long before the bot gives up searching in one direction
int attackCount;    // counter for how long robot attacks for
int threshold;      //threshold for line sensors
int prevIR;         // past time IR sensors were polled
int cur;            // current timer
int prevFlag;       // timer for some movement
int prevLine;       // past time line sensors were polled
int state;          // movement state of robot
int rangeThresh;    // also not sure about this
int lineFlag;       // flag to mark if line has been met
boolean pivotFlag;  // flag to mark if the robot has pivoted
boolean pastNear; // flag to mark if the opponent was near the robot last
int speedArrR[5]; //running average for calculating velocity
int speedArrL[5];
int expectedVelR; //expected velocity
int expectedVelL;
bool prevHallR; //if at previous measurement the hallsensor was on
bool prevHallL;
nt arrPosR; //pointer to insert values in the speed array
int arrPosL;
bool pastStalled;
int stalled;
int initial;

// thresholds for distance sensors
int near = 200;
int far = 500;
int dist = 150;

// thresholds for movement timers
int degreesMin = 20; // turn a little
int degrees90 = 50; // turn 90 degrees
int degrees180 = 100; // turn 180 degrees
int startSpinR = 7000; // time spinning right at start
int startTurnL = 2000; // time turning left at start
int startSpinL = 5000; // time spinning left at start
int startCross = 1000; // time crossing the arena
int pivotBack = 500; // time moving back at pivot
int pivotSpinR = 1000; // time spinning right at pivot
int pivotTurnL = 1000; // time turning left at pivot
int pivotSpinL = 1000; // time spinning left at pivot
int stallThresh = 500; // time stalled
int hallTimeThresh = 100;

// max and minimum motor speeds
int maxS = 200;
int minS = 150;

void setup() {
  Serial.begin(9600);

  R_ESC.attach(10);
  L_ESC.attach(11);
  R_ESC.writeMicroseconds(1500);
  L_ESC.writeMicroseconds(1500);

  pinMode(L_Hall, INPUT);
  pinMode(R_Hall, INPUT);

  // basic start module: wait 5s after pressing start
  // IMPLEMENT ON/OFF functionality
    // for OFF:
      // either have permanent off until power cycle
      // or reset timer, variables, and such
  pinMode(startModule, INPUT);
  initial = digitalRead(startModule);
  while (initial == digitalRead(startModule)) {
    Serial.println(digitalRead(startModule));
  }
  delay(5000);
  initial = digitalRead(startModule);
  
  past = 'f'; //set default move to forward
  searchCount = 0;
  attackCount = 0;
  threshold = analogRead(BL) - 200; // set start value for line sensors to compare
  rightDist = rightMidIR.getDist(); // poll right sensor
  leftDist = leftMidIR.getDist(); // poll left sensor
  perRightDist = rightPerIR.getDist(); // poll peripheral right sensor
  perLeftDist = leftPerIR.getDist(); // poll peripheral left sensor
  prevLine = millis();
  prevIR = prevLine;
  lineFlag = 0;
  pivotFlag = true;
  pastNear = false;
  prevFlag = prevLine;
  for (int i = 0; i < 5; i++) {
    speedArrR[i] = prevLine;
    speedArrL[i] = prevLine;
  }
  arrPosR = 0;
  arrPosL = 0;
  prevHallR = false;
  prevHallL = false;
  state = 11; // at start, movement state is the startup state
  pastStalled = false;
  stalled = false;
}

void loop() {
  if (initial != digitalRead(startModule)) {
    stop();
    while(1) {}
  }
  cur = millis();
//  if (digitalRead(R_Hall), HIGH) {
//    if (!prevHallR) {
//      prevHallR = true;
//      speedArrR[arrPosR % 5] = cur;
//      arrPosR++;
//    } else {
//      prevHallR = false;
//    }
//  }
//  if (digitalRead(L_Hall), HIGH) {
//    if (!prevHallL) {
//      prevHallL = true;
//      speedArrL[arrPosL % 5] = cur;
//      arrPosL++;
//    } else {
//      prevHallL = false;
//    }
//  }
  movement(state);
  //  perLeftDist += 350;

  //print out values from sensors and motors to the console
  //Serial.print(past);
  //Serial.print(", ");
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
    if ((analogRead(BL) < threshold || analogRead(BR) < threshold) && lineFlag != 1) {
      //if line detected by back line sensors and wasn't detected before, go forward
      state = 0;
      lineFlag = 1; // set line flag state
      prevFlag = cur;
      pivotFlag = false;
      pastNear = false;
      stop();
    } else if (analogRead(FL) < threshold && past == 'l' && lineFlag != 2) {
      // if past left and front left hits line and wasn't hit before, turn back right, spin left
      state = 6;
      lineFlag = 2; // set line flag state
      prevFlag = cur;
      pivotFlag = false;
      pastNear = false;
    } else if (analogRead(FL) < threshold && past == 'r' || analogRead(FL) < threshold && past == 'f' && lineFlag != 3) {
      // if past right or forward and front left hits line and wasn't hit before, turn back right, spin right
      state = 7;
      lineFlag = 3; // set line flag state
      prevFlag = cur;
      pivotFlag = false;
      pastNear = false;
      stop();
    } else if (analogRead(FR) < threshold && past == 'l' && lineFlag != 4) {
      // if past left and front right hits line and wasn't hit before, turn back left, spin right
      state = 8;
      lineFlag = 4; // set line flag state
      prevFlag = cur;
      pivotFlag = false;
      pastNear = false;
      stop();
    } else if (analogRead(FR) < threshold && past == 'r' || analogRead(FR) < threshold && past == 'f' && lineFlag != 5) {
      // if past right or forward and front right hits line and wasn't hit before, turn back left, spin left
      state = 9;
      lineFlag = 5; // set line flag state
      prevFlag = cur;
      pivotFlag = false;
      pastNear = false;
      stop();
    } else if (analogRead(FR) < threshold && analogRead(FL) < threshold && lineFlag != 6) {
      // if both front corners hits line and wasn't hit before, go back and spin 180 degrees
      state = 10;
      lineFlag = 6; // set line flag state
      prevFlag = cur;
      pivotFlag = false;
      pastNear = false;
      stop();
    } 
  if ((cur - prevIR) >= 25) {
      // otherwise, poll all the distance sensors
      prevIR = cur;
      rightDist = rightMidIR.getDist();
      leftDist = leftMidIR.getDist();
      perRightDist = rightPerIR.getDist();
      perLeftDist = leftPerIR.getDist();

      //attack code with sensors
      if (past == 'f' && attackCount < 50) {
        // if (!pastStalled){
        //   stalled = cur;
        //   pastStalled = true;
        // } else if (cur - stalled > stallThresh) {
          state = 12;
          pivotFlag = true;
        // }   
      } 
      // else if (pastStalled) {
      //   pastStalled = false;
      // }

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
        } 
        // else if ((expectedVelL > getVelL() + hallTimeThresh || expectedVelR > getVelR() + hallTimeThresh) && pastStalled && cur - stalled <= stallThresh) {
        //   past = 'f';
        //   state = 1;
        //   attackCount++; // increment attack counter
        //   pastNear = true;
        // } 
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
          if ((abs(rightDist - leftDist) <= dist)
                || ((past == 'f' || searchCount >= 100) && (rightDist > far && leftDist > far && perRightDist > far && perLeftDist > far))) {
            //if (robot moved forward in the past OR it's been searching for 100 iterations) AND (there isn't an object within far of any IR sensor))
            //move forward
            state = 0;
            past = 'f'; //set past movement to forward
            searchCount = 0; //reset abandon search count
            pastNear = false;
            attackCount = 0;
          } else if ((leftDist <= far || perLeftDist <= far) || leftDist - rightDist < -dist) {
            // if opponent within far of the left sensors or if difference within some negative threshold, move left
            state = 2;
            past = 'l'; //set past movement to left
            searchCount = 0; //reset abandon search count because the robot has found an object
            pastNear = false;
            attackCount = 0;
          } else if ((rightDist <= far || perRightDist <= far) || leftDist - rightDist > dist) {
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

  // pin 10 is Right ESC
  // pin 11 is Left ESC
  // usage: x_ESC.writeMicroseconds(pwm)
  // pwm should between 1100 and 1800
  // 1100 for maximum reverse, 1800 for maximum forward
  // 30% throttle is 1500 +/- 300*0.3 = 1500 +/- 90

  int pwm = 1500;       // default is ESC stopped
  // "speed" is from 0 to 255
  int mapped = map(speed, 0, 255, 0, 150);
  if (motor == 2) {
    mapped = -mapped;
  }
  if(direction == 1) {  // forward
    pwm = 1500 + mapped;
  } else {              // reverse
    pwm = 1500 - mapped;
  }
  if(motor == 1) {      // RIGHT ESC
    R_ESC.writeMicroseconds(pwm);
  } else {              // LEFT ESC
    L_ESC.writeMicroseconds(pwm);
  }
}

void stop(){
  R_ESC.writeMicroseconds(1500);
  L_ESC.writeMicroseconds(1500);
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
