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

/*
 * SUMO DIAGNOSTICS
 * Simple program to check all active sensors
 */

#include <SharpDistSensor.h>
#include <Servo.h>  // for ESCs

/* labeled wrong on PCB
 *  solution: keep connector positions but change pin declarations as described below:
 *  FL is A0
 *  FR is A1
 *  BL is A2
 *  BR is A3
 */

// Analog pin to which the sensor is connected
const byte BR = A3;           // back-right line sensor
const byte BL = A2;           // back-left line sensor
const byte FR = A1;           // front-right line sensor
const byte FL = A0;           // front-left line sensor

const byte LLO = A4;          // left-peripheral IR distance sensor
const byte LMO = A5;          // left-middle IR distance sensor
const byte RMO = A6;          // right-middle IR distance sensor
const byte RRO = A7;          // right-peripheral IR distance sensor

const byte L_Hall = 2;        // left Hall sensor
const byte R_Hall = 3;        // right Hall sensor
const byte startModule = 4;   // remote start module

// Window size of the median filter (odd number, 1 = no filtering)
const byte mediumFilterWindowSize = 5;

// Create an object instance of the SharpDistSensor class
SharpDistSensor rightMidIR(RMO, mediumFilterWindowSize);  // RMO
SharpDistSensor leftMidIR(LMO, mediumFilterWindowSize);   // LMO
SharpDistSensor rightPerIR(RRO, mediumFilterWindowSize);  // RRO
SharpDistSensor leftPerIR(LLO, mediumFilterWindowSize);   // LLO

Servo L_ESC;  //Left Motor
Servo R_ESC;  //Right Motor

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
  int initial = digitalRead(startModule);
  while (initial == digitalRead(startModule)) {
    //Serial.println(digitalRead(startModule));
  }
  delay(5000);
}

void loop() {
  Serial.print("BR: ");
  Serial.println(analogRead(BR));
  Serial.print("BL: ");
  Serial.println(analogRead(BL));
  Serial.print("FR: ");
  Serial.println(analogRead(FR));
  Serial.print("FL: ");
  Serial.println(analogRead(FL));
  Serial.print("L_Hall: ");
  Serial.println(digitalRead(L_Hall));
  Serial.print("R_Hall: ");
  Serial.println(digitalRead(R_Hall));
  Serial.println("RRO   RMO   LMO    LLO ");
  Serial.print(rightPerIR.getDist());
  Serial.print("  ");
  Serial.print(rightMidIR.getDist());
  Serial.print("  ");
  Serial.print(leftMidIR.getDist());
  Serial.print("   ");
  Serial.println(leftPerIR.getDist());
  Serial.println();
  Serial.println();
  Serial.println();
  Serial.println();
  delay(500);
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
  if(direction == 1) {  // forward
    pwm = 1500 + map(speed, 0, 255, 0, 300);
  } else {              // reverse
    pwm = 1500 - map(speed, 0, 255, 0, 300);
  }

  if(motor == 1) {      // RIGHT ESC
    R_ESC.writeMicroseconds(pwm);
  } else {              // LEFT ESC
    L_ESC.writeMicroseconds(pwm);
  }
}

void stop(){
  //enable standby
  //digitalWrite(STBY, LOW);
  R_ESC.writeMicroseconds(1500);
  L_ESC.writeMicroseconds(1500);
}
