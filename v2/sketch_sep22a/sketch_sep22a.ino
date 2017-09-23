// Testing the traxxas VXL 3s ESC by Seth Bergman. This works on mine from my Traxxas Rustler VXL.
// Please use with caution. I started with the Servo sketch by  Michal Rinott.

#include <Servo.h>  ;  // create servo object to control a servo 

Servo VXL3sMotor;

int brakeLevel = 0;
int currentSpeed = 0;
int j = 1;
int i = 0;
const int maxNum = 30;  //up to 90? 
int delayTime = 50;


void setup() 
{ 
  Serial.begin(9600);
  VXL3sMotor.attach(12);  // attaches the servo on pin 9 to the servo object 
  motor(0);
  delay(150);
} 

void loop() {
  
  Serial.println();
  Serial.println("Checking Forward");
  checkForward(); 
  Serial.println();
  Serial.println("Checking Reverse");
  checkReverse(); 

} 

void motor(int val){
  Serial.println(val);
  val = val + 90;
  VXL3sMotor.write(val);
}

void brake(int level){

  switch(level){
  case 0:
    Serial.println("Hard Stop");
    motor(-2*currentSpeed);
    //delay(abs(currentSpeed));
    delay(100); //minimum delay for the motor to react to a direction change is 100ms
    motor(0);
    break; 

  case 1:
    motor(-currentSpeed);
    Serial.println("Soft Stop");
    delay(abs(currentSpeed)* 20);
    delay(1000);
    motor(0);
    break; 

  case 2:
    motor(0);
    Serial.println("Coast Stop");
    delay(abs(currentSpeed) * 70);
    delay(1000);
    motor(0);
    break; 
  }
}
void checkForward(){
  int step = 30;
  int i = 0;
 
    for (int i = -step + step; i < step+1; i++){
      currentSpeed = i;
      delay(delayTime);
      motor(currentSpeed);
    }
    /*if (currentSpeed > .8 * maxNum) brake(2); //keeps from braking too hard
    else if (currentSpeed >.5 * maxNum) brake(1); //keeps from braking too hard
    else*/ brake(brakeLevel);
      
//    j++;
//    step += 5;
//    if (brakeLevel == 2) brakeLevel = 0;
//    else brakeLevel ++;
//    if (j == 6){
//      j = 1; 
//    } 
  
}

void checkReverse(){
  brakeLevel = 0;
  int step = -30;
  int i = 0;
    for (int i = -step + step; i > step-1; i--){
      currentSpeed = i;
      delay(delayTime);
      motor(currentSpeed);
    }
    /* if (abs(currentSpeed) > .8 * maxNum) brake(2); //keeps from braking too hard
    else if (abs(currentSpeed) >.5 * maxNum) brake(1); //keeps from braking too hard
    else*/ brake(brakeLevel);
//    j++;
//    step -= 5;
//    if (brakeLevel == 2) brakeLevel = 0;
//    else brakeLevel ++;
//    if (j == 6){
//      j = 1; 
//    } 
  
}
