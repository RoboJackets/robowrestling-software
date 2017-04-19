#include <Servo.h>

//Start button
//Used: Cherry (limit) switch (normally closed)
//Since this is NC, pin is pulled down with switch on high side
#define button 6

//BLDC ESC parameters
//Used: VXL-3s Traxxas Single Channel ESCs
Servo leftMotor, rightMotor;
#define leftMotPin  10 
#define rightMotPin 9

//Line sensor parameters
//Used: RPR-220
//LF = left front, LB = left back
//RF = right front, RB = right back
#define LFinput A0
#define LFled   5
#define LBinput A1
#define LBled   4
#define RFinput A2
#define RFled   3
#define RBinput A3
#define RBled   2

int inputPins[4] = {LFinput, LBinput, RFinput, RBinput};
int ledPins[4] = {LFled, LBled, RFled, RBled};

#define lineThreshold 100
boolean initialize = true;
long LFbaseVal, LBbaseVal, RFbaseVal, RBbaseVal;
long bvals[4] = {LFbaseVal, LBbaseVal, RFbaseVal, RBbaseVal};
long LFval, LBval, RFval, RBval;
long vals[4] = {LFval, LBval, RFval, RBval};

//Ultrasonic range finder parameters
//Used: HC-SR04
#define leftEcho 11
#define leftTrig 12
#define rightEcho 8
#define rightTrig 7

//Distance parameters
#define maxRange 20
#define minRange 1
long leftDistance = 1000;
long rightDistance = 1000;
long prevLeft, prevRight;
long durationLeft, durationRight;

//Search parameters
boolean found = false; //true when enemy located
boolean lost = false;  //true after enemy located for first time

//Follow parameters
boolean tagged = false; //unclear usage

//Motor speed parameters
#define baseSpeed 128
int leftMod = 0;
int rightMod = 0;
int leftSpeed = 0;
int rightSpeed = 0;

//Motor direction parameters
int diff;
int diffMag;
int leftDir = 0;
int rightDir = 1;

void setup() {
  Serial.begin(9600);

  pinMode(button, INPUT);
  
  pinMode(LFinput, INPUT);
  pinMode(LFled, OUTPUT);
  pinMode(LBinput, INPUT);
  pinMode(LBled, OUTPUT);
  pinMode(RFinput, INPUT);
  pinMode(RFled, OUTPUT);
  pinMode(RBinput, INPUT);
  pinMode(RBled, OUTPUT);
  
  pinMode(leftTrig, OUTPUT);
  pinMode(leftEcho, INPUT);
  pinMode(rightTrig, OUTPUT);
  pinMode(rightEcho, INPUT);

  leftMotor.attach(leftMotPin);
  rightMotor.attach(rightMotPin);
  
  start();
  readLine();
}

void loop() {
  search();
}

//start, wait 5s after release of button
void start() {
  while(true) {
    if(digitalRead(button) == HIGH) { //if pressed
      //for user, hold button until referee says so
      //upon release
      delay(500); //half sec delay to filter bounces
      while(true) {
        if(digitalRead(button) == LOW) {
          delay(5000);
          return;
        }
      }
    }
  }
}

//readLine
void readLine() {   //line sensors take calibration reading
 int ambient = 0;
 int lit = 0;
 int value = 0;
 //ORDER: LF LB RF RB
 for(int k = 0; k < 4; k++) {
  digitalWrite(ledPins[k], LOW);
  delay(5);   //To give ADC and LED transition time
  ambient = analogRead(inputPins[k]);
  digitalWrite(ledPins[k], HIGH);
  delay(5);
  lit = analogRead(inputPins[k]);
  if(initialize) {
    bvals[k] = lit - ambient;
  }
  vals[k] = lit - ambient;
 }
 if(!initialize) {
  checkLine();
 } else {
  initialize = false;
  Serial.println("initialization done.");
 }
}

//checkLine
void checkLine() {
  for(int j = 0; j < 4; j++) {
    if((vals[j] - bvals[j]) >= lineThreshold) {
      recovery(j+1);
      return;
    }
  }
}

//recovery
void recovery(int sensor) {
  // 0 is forward, 1 is backward
  //move(1, 200, rightDir); //right motor
  //move(2, 200, leftDir); //left motor
  switch(sensor) {
    case 1:   //front, burst of back up
      Serial.println("LF TRIGGERED");
      //burst backward, reverse right
      move(1, 255, 1);
      move(2, 255, 1);
      delay(500);
      move(1, 50, 1);
      move(2, 255, 1);
      delay(500);
      break;
    case 2:
      Serial.println("LB TRIGGERED");
      //burst forward, fwd right
      move(1, 255, 0);
      move(2, 255, 0);
      delay(500);
      move(1, 50, 0);
      move(2, 255, 0);
      delay(500);
      break;
    case 3:   //right, burst forward, back up to left
      Serial.println("RF TRIGGERED");
      //burst backward, reverse left
      move(1, 255, 1);
      move(2, 255, 1);
      delay(500);
      move(1, 255, 1);
      move(2, 50, 1);
      delay(500);
      break;
    case 4:   //
      Serial.println("RB TRIGGERED");
      //burst forward, fwd left
      move(1, 255, 0);
      move(2, 255, 0);
      delay(500);
      move(1, 255, 0);
      move(2, 50, 0);
      delay(500);
      break;
  }
}

//move
void move(int motor, int speed, int direction) {
  //motor: LEFT 0 RIGHT 1
  //speed: 0 is off, and 255 is full speed
  //direction: 0 FWD, 1 REV
  //^ double check conventions
  int ppmSpeed;
  if(direction == 0) {  //FWD
    ppmSpeed = 1500 + 400*(speed/255); 
  } else {              //REV
    ppmSpeed = 1500 - 400*(speed/255);
  }
  if(motor == 2) {  //Left,   2
    leftMotor.writeMicroseconds(ppmSpeed);
  } else {          //Right , 1
    rightMotor.writeMicroseconds(ppmSpeed);
  }
}

//stop
void stop() {
  leftMotor.writeMicroseconds(1500);
  rightMotor.writeMicroseconds(1500);
  delay(250); //this is near the mininum delay required for a quick reverse
}

//calcDistance
void calcDistance() {
 prevLeft = leftDistance;
 prevRight = rightDistance;
 //The following trigPin/echoPin cycle is used to determine the
 //distance of the nearest object by bouncing soundwaves off of it.
 //Calculate the distance (in cm) based on the speed of sound.
 delay(10);
 digitalWrite(leftTrig, LOW);
 delayMicroseconds(5);
 digitalWrite(leftTrig, HIGH);
 delayMicroseconds(10);
 digitalWrite(leftTrig, LOW);
 pinMode(leftEcho, INPUT);
 durationLeft = pulseIn(leftEcho, HIGH);
 leftDistance = durationLeft/58.2;  

 delay(10);

 digitalWrite(rightTrig, LOW);
 delayMicroseconds(5);
 digitalWrite(rightTrig, HIGH);
 delayMicroseconds(10);
 digitalWrite(rightTrig, LOW);
 pinMode(rightEcho, INPUT);
 durationRight = pulseIn(rightEcho, HIGH);
 rightDistance = durationRight/58.2; 

 readLine();
}
//search
void search() {
  while(!found) {
    // 0 is forward, 1 is backward
    move(1, 200, rightDir); //right motor
    move(2, 200, leftDir); //left motor
    calcDistance();
    //Serial.print("left: ");
    Serial.print(leftDistance);
    Serial.print(",");
    Serial.println(rightDistance);
    //delay(10);
    if(lost) {
      if(diff>0){//turn right
        rightDir = 0;
        leftDir = 1;
      } else {//turn left
        rightDir = 1;
        leftDir = 0;
      }
    }
    if((leftDistance <= maxRange && leftDistance >= minRange) &&
       (rightDistance <= maxRange && rightDistance >=minRange)) {
        found = true;
        //Serial.println("FOUND");
      stop();  
      follow();
      //uncomment for looped testing of search function  
      //delay(1000);
      //found = false;
    }
  }
}

//follow
void follow() {
  while(!tagged) {
    calcDistance();
    diff = leftDistance - rightDistance;
    diffMag = abs(diff);

    if(!(leftDistance <= maxRange && leftDistance >= minRange) &&
       !(rightDistance <= maxRange && rightDistance >=minRange)) {
        found = false;
        lost = true;
        search();
    }
    
    if(diff > 0 && diffMag > 2) {
        leftMod = 100*(diffMag/rightDistance);
        //Serial.println("R");
    } else if(diff < 0 && diffMag > 2) {
        rightMod = 100*(diffMag/leftDistance);
        //Serial.println("L");
    } else {
        leftMod = 100;
        rightMod = 100;
        //Serial.println("F");
    }
    leftSpeed = baseSpeed + leftMod;
    rightSpeed = baseSpeed + rightMod;
    //Serial.print("left: ");
    Serial.print(leftDistance);
    Serial.print(",");
    Serial.println(rightDistance);
    
    move(1, leftSpeed, 0);
    move(2, rightSpeed, 0);
  }
}
