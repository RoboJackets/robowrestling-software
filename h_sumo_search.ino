
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

#define leftEcho 2  // left Echo Pin
#define leftTrig 4  // left Trigger Pin
#define rightEcho 7 // right Echo Pin
#define rightTrig 6 // right Trigger Pin

// POSSIBLY CHANGE THIS FOR ARENA SIZE
int maximumRange = 150; // Maximum range needed
int minimumRange = 1; // Minimum range needed
long leftDistance = 1000;
long rightDistance = 1000;
long prevLeft;
long prevRight;
long durationLeft, cmLeft, inchesLeft, cmRight, inchesRight, durationRight;
long lD[] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
long rD[] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
int iterator = 0;

boolean found = false;  // used for search()
boolean lost = false;

boolean tagged = false; // used for follow()
int rightDirMod = 0;
int leftDirMod = 0;

//------------------------------
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
//-----------------------------

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

  //search();
}

void loop(){
  search();
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
  if (iterator == 20) {
    iterator = 0;
  }
  prevLeft = leftDistance;
  prevRight = rightDistance;
/* The following trigPin/echoPin cycle is used to determine the
 distance of the nearest object by bouncing soundwaves off of it. */ 
// digitalWrite(leftTrig, LOW); 
// delayMicroseconds(2); 
// digitalWrite(leftTrig, HIGH);
// delayMicroseconds(10); 
// digitalWrite(leftTrig, LOW);
// duration = pulseIn(leftEcho, HIGH);
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
 
// digitalWrite(rightTrig, LOW); 
// delayMicroseconds(2); 
// digitalWrite(rightTrig, HIGH);
// delayMicroseconds(10); 
// digitalWrite(rightTrig, LOW);
// duration = pulseIn(rightEcho, HIGH);
  digitalWrite(rightTrig, LOW);
  delayMicroseconds(5);
  digitalWrite(rightTrig, HIGH);
  delayMicroseconds(10);
  digitalWrite(rightTrig, LOW);
  pinMode(rightEcho, INPUT);
  durationRight = pulseIn(rightEcho, HIGH);
 //Calculate the distance (in cm) based on the speed of sound.
 rightDistance = durationRight/58.2;  

// if((leftDistance<minimumRange)||(leftDistance>maximumRange)) {
//  leftDistance = prevLeft;
// }
// if((rightDistance<minimumRange)||(rightDistance>maximumRange)) {
//  rightDistance = prevRight;
// }

//button
//esc code
 
// iterator++;
// leftDistance = 0;
// rightDistance = 0;
// for (int j= 0; j < 20; j++) {
//  leftDistance += lD[j];
//  rightDistance += rD[j];
// }
// leftDistance = leftDistance/20;
// rightDistance = rightDistance/20;
}

/*
 * spins until it finds an object, then stops
 */
void search() {
  while(!found) {
    // 0 is forward, 1 is backward
    move(1, 128, rightDir); //right motor
    move(2, 128, leftDir); //left motor
    calcDistance();
    //Serial.print("left: ");
    Serial.print(leftDistance);
    Serial.print(",");
    Serial.println(rightDistance);
    delay(10);
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
        leftMod = 50*(diffMag/rightDistance);
        //Serial.println("R");
    } else if(diff < 0 && diffMag > 2) {
        rightMod = 50*(diffMag/leftDistance);
        //Serial.println("L");
    } else {
        leftMod = 50;
        rightMod = 50;
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

  /*
   * loop
   * move toward object
   *    if left sensor is closer, slight turn left
   *    if right sensor is closer, slight turn right
   *    if both are pretty much same, keep straight
   *    stop when both sensor's distance is lower than 10
   * have a constant for the degree of turn
   * 
   * if robot loses sight (sensors output -1, do search again)
   */




