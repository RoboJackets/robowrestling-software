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
int AIN1 = 9; //Direction
int AIN2 = 8; //Direction

//Motor B
int PWMB = 5; //Speed control
int BIN1 = 11; //Direction
int BIN2 = 12; //Direction

#define leftEcho 2  // left Echo Pin
#define leftTrig 4  // left Trigger Pin
#define rightEcho 7 // right Echo Pin
#define rightTrig 6 // right Trigger Pin

// POSSIBLY CHANGE THIS FOR ARENA SIZE
int maximumRange = 20; // Maximum range needed
int minimumRange = 0; // Minimum range needed
long duration, leftDistance, rightDistance; // Duration used to calculate distance

boolean found = false;  // used for search()

boolean tagged = false; // used for follow()
int rightDirMod = 0;
int leftDirMod = 0;

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
  follow();
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
/* The following trigPin/echoPin cycle is used to determine the
 distance of the nearest object by bouncing soundwaves off of it. */ 
 digitalWrite(leftTrig, LOW); 
 delayMicroseconds(2); 
 digitalWrite(leftTrig, HIGH);
 delayMicroseconds(10); 
 digitalWrite(leftTrig, LOW);
 duration = pulseIn(leftEcho, HIGH);
 //Calculate the distance (in cm) based on the speed of sound.
 leftDistance = duration/58.2;  
 
 digitalWrite(rightTrig, LOW); 
 delayMicroseconds(2); 
 digitalWrite(rightTrig, HIGH);
 delayMicroseconds(10); 
 digitalWrite(rightTrig, LOW);
 duration = pulseIn(rightEcho, HIGH);
 //Calculate the distance (in cm) based on the speed of sound.
 rightDistance = duration/58.2;  
}

/*
 * spins until it finds an object, then stops
 */
void search() {
  while(!found) {
    // 0 is forward, 1 is backward
    move(1, 128, 1); //right motor
    move(2, 128, 0); //left motor
    calcDistance();
    Serial.println(leftDistance);
    Serial.println(rightDistance);
    delay(10);
    if((leftDistance <= maximumRange && leftDistance >= minimumRange) ||
       (rightDistance <= maximumRange && rightDistance >=minimumRange)) {
        found = true;
        Serial.println("FOUND");
      stop();  
      //uncomment for looped testing of search function  
      //delay(1000);
      //found = false;
    }
  }
}

void follow() {
  while(!tagged) {
    //happens every loop
    move(1, 128, rightDirMod); //right motor with rightDirMod
    move(2, 128, leftDirMod); //left motor with leftDirMod

    Serial.println(leftDistance);
    Serial.println(rightDistance);
    
    //change dir
    //0 is forward, 1 is backward
    if((leftDistance - rightDistance) > 10 ) {
      //if right sensor is closer, slight turn right
      rightDirMod = 0;
      leftDirMod = 1;
    } else if((leftDistance - rightDistance) < -10) {
      //if left sensor is closer, slight turn left
      rightDirMod = 1;
      leftDirMod = 0;
    } else {
      rightDirMod = 0;
      leftDirMod = 0;
    }
    calcDistance();
    if((leftDistance <= 5 && leftDistance >= minimumRange) ||
         (rightDistance <= 5 && rightDistance >=minimumRange)) {
          tagged = true;
          Serial.println("GOTCHA");
        stop();  
    }
    delay(10);
  } 
  while(true) {
    stop();
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




