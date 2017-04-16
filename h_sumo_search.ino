
/*
 * autonomous sumo test 1
 * simple h bridge controlling 2-wheel bot
 * HC-SR04 used for object detection
 * objective: search and push
*/

//motor A connected between A01 and A02
//motor B connected between B01 and B02

int STBY = 10; //standby

//Motor A
int PWMA = 3; //Speed control
int AIN1 = 8; //Direction
int AIN2 = 9; //Direction

//Motor B
int PWMB = 5; //Speed control 
int BIN1 = 12; //Direction
int BIN2 = 11; //Direction

//HC-SR04
#define leftEcho 2  // left Echo Pin
#define leftTrig 4  // left Trigger Pin
#define rightEcho 7 // right Echo Pin
#define rightTrig 6 // right Trigger Pin

// Distance variables and parameters
#define maximumRange 20 // Maximum range needed
#define minimumRange 1  // Minimum range needed
long leftDistance = 1000;
long rightDistance = 1000;
long prevLeft, prevRight;
long durationLeft, cmLeft, inchesLeft, cmRight, inchesRight, durationRight;

//search()
boolean found = false;  // used for search()
boolean lost = false;   // true after enemy is found for first time

//follow()
boolean tagged = false;
int rightDirMod = 0;
int leftDirMod = 0;

//speed variables and parameters
#define baseSpeed 128
int leftMod = 0;
int rightMod = 0;
int leftSpeed = 0;
int rightSpeed = 0;

int speedModifier;
int diff;
int diffMag;

int leftDir = 0;
int rightDir = 1;

//line sensor pins(temporarily RPR-220)
#define frontInput  A0
#define frontLed    13
#define leftInput   A1
#define leftLed     17
#define rightInput  A2
#define rightLed    18

//line sensor variables and parameters
#define lineThreshold 100
boolean initialize = true;
long frontBaseVal, leftBaseVal, rightBaseVal;
long frontVal, leftVal, rightVal;

void setup(){
  Serial.begin (9600);
  pinMode(STBY, OUTPUT);

  pinMode(PWMA, OUTPUT);
  pinMode(AIN1, OUTPUT);
  pinMode(AIN2, OUTPUT);

  pinMode(PWMB, OUTPUT);
  pinMode(BIN1, OUTPUT);
  pinMode(BIN2, OUTPUT);

  pinMode(leftTrig, OUTPUT);
  pinMode(leftEcho, INPUT);
  pinMode(rightTrig, OUTPUT);
  pinMode(rightEcho, INPUT);

  pinMode(frontInput, INPUT);
  pinMode(leftInput, INPUT);
  pinMode(rightInput, INPUT);
  pinMode(frontLed, OUTPUT);
  pinMode(leftLed, OUTPUT);
  pinMode(rightLed, OUTPUT);
  
  readLine();
}

void loop(){
  search();
}

//line sensors take calibration reading
void readLine() {
 int ambient = 0;
 int lit = 0;
 int value = 0;

 digitalWrite(frontLed, LOW);
 delay(5);                            //To give ADC and LED transition time
 ambient = analogRead(frontInput);
 digitalWrite(frontLed, HIGH);
 delay(5);
 lit = analogRead(frontInput);
 if(initialize) {
  frontBaseVal = lit - ambient;  
 }
 frontVal = lit - ambient;
 
 digitalWrite(leftLed, LOW);
 delay(5);                            //To give ADC and LED transition time
 ambient = analogRead(leftInput);
 digitalWrite(leftLed, HIGH);
 delay(5);
 lit = analogRead(leftInput);
 if(initialize) {
  leftBaseVal = lit - ambient;
 }
 leftVal = lit - ambient;
 
 digitalWrite(rightLed, LOW);
 delay(5);                            //To give ADC and LED transition time
 ambient = analogRead(rightInput);
 digitalWrite(rightLed, HIGH);
 delay(5);
 lit = analogRead(rightInput);
 if(initialize) {
  rightBaseVal = lit - ambient;
 }
 rightVal = lit - ambient;
 if(!initialize) {
  checkLine();
 } else {
  initialize = false;
  Serial.println("initialization done.");
 }
}

void checkLine() {
  if((frontVal - frontBaseVal) >= lineThreshold) {
    recovery(1);
    return;
  }
  if((leftVal - leftBaseVal) >= lineThreshold) {
    recovery(2);
    return;
  }
  if((rightVal - rightBaseVal) >= lineThreshold) {
    recovery(3);
    return;
  }
}

void recovery(int sensor) {
  // 0 is forward, 1 is backward
  //move(1, 200, rightDir); //right motor
  //move(2, 200, leftDir); //left motor
  switch(sensor) {
    case 1:   //front, burst of back up
      Serial.println("FRONT TRIGGERED");
      move(1, 255, 1);
      move(2, 255, 1);
      delay(1000);
      break;  //left, burst forward, back up to right
    case 2:
      Serial.println("LEFT TRIGGERED");
      move(1, 255, 0);
      move(2, 255, 0);
      delay(500);
      move(1, 128, 1);
      move(2, 255, 1);
      delay(500);
      break;
    case 3:   //right, burst forward, back up to left
      Serial.println("RIGHT TRIGGERED");
      move(1, 255, 1);
      move(2, 255, 1);
      delay(500);
      move(2, 128, 1);
      move(1, 255, 1);
      delay(500);
      break;
  }
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

/*
 * spins until it finds an object, then stops
 */
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
    if((leftDistance <= maximumRange && leftDistance >= minimumRange) &&
       (rightDistance <= maximumRange && rightDistance >=minimumRange)) {
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

void follow() {
  while(!tagged) {
    calcDistance();
    diff = leftDistance - rightDistance;
    diffMag = abs(diff);

    if(!(leftDistance <= maximumRange && leftDistance >= minimumRange) &&
       !(rightDistance <= maximumRange && rightDistance >=minimumRange)) {
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
