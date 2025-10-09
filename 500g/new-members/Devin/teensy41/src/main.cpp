#include <Arduino.h>
#include "World_State.hpp"
#include "motorActions.hpp"
#include "algorithms.hpp"

const int left = 2;
const int middle = 3;
const int right = 4;

const int LeftLineSensor= 23;
const int RightLIneSensor= 22;
const int START_PIN = 0; 

const int rightFWD = 5;
const int rightBack = 6;
const int leftFWD = 7;
const int leftBack = 8;

int* motors  = new int[2];
int* line_sensors = new int[2];
int* ir_sensors = new int[3];
World_State* ws =  new World_State(line_sensors, ir_sensors);
motorActions* ma = new motorActions(motors, ir_sensors, line_sensors);
Algorithms* alg = new Algorithms(ma, ws);


void setup() {
 
 pinMode(left, INPUT);
 pinMode(middle, INPUT);
 pinMode(right, INPUT);
 pinMode(START_PIN, INPUT);
 pinMode(rightFWD, OUTPUT);
 pinMode(rightBack, OUTPUT);
 pinMode(leftFWD, OUTPUT); 
 pinMode(leftBack, OUTPUT);
 pinMode(LeftLineSensor, INPUT);
pinMode(RightLIneSensor, INPUT);
 Serial.begin(9600);
 
//  int i = 0;
//   while(digitalRead(START_PIN) == 0){
//     if(i%200 ==0){
//       Serial.println("Waiting");

//     }
//     i++;
//   }

}

void pullSensors();
void writeMotors();
void debugLine();
void debugIR();
void debugEnemy(EnemyPosition ep);

void loop() {
  int j=0;
  
  // if(digitalRead(START_PIN) == 1){
    pullSensors();
    ws->checkConcurrency();
     alg->respondToEnemy();  
    writeMotors();
    if(j%500000==0){
    debugIR();
    EnemyPosition ep = ws->enemy_pos();
    debugEnemy(ep);
   
    }
    j++;
//   }
//   else{
//    Serial.println("STOPPED");
    
//  }
 

  

}
void debugEnemy(EnemyPosition ep){
  switch(ep) {
    case NONE:     Serial.print("NONE"); break;
    case LEFT:     Serial.print("LEFT"); break;
    case FRONT:    Serial.print("FRONT"); break;
    case RIGHT:    Serial.print("RIGHT"); break;
    case MIDLEFT:  Serial.print("MIDLEFT"); break;
    case MIDRIGHT: Serial.print("MIDRIGHT"); break;
    case FARFRONT: Serial.print("FARFRONT"); break;
  }
  Serial.println();
}
void debugLine(){
  for(int i = 0; i < 2; i++){
         Serial.print(line_sensors[i]);
         Serial.print(" ");
     }

}

void debugIR(){
  for(int i = 0; i < 3; i++){
         Serial.print(ir_sensors[i]);
         Serial.print(" ");
     }
   
}
void writeMotors(){
  if(motors[0] >0){
     analogWrite(rightFWD, motors[0]);
     analogWrite(rightBack,0);
  }
  else if (motors[0]==0){
    analogWrite(rightBack, 255);
    analogWrite(rightFWD, 255);
  }
  else{
    analogWrite(rightBack, abs(motors[0]));
    analogWrite(rightFWD,0);
  }

  if(motors[1] >0){
     analogWrite(leftFWD, motors[1]);
     analogWrite(leftBack,0);
  }
  else if (motors[1]==0){
    analogWrite(leftBack, 255);
    analogWrite(leftFWD, 255);
  }
  else{
    analogWrite(leftBack, abs(motors[1]));
    analogWrite(leftFWD,0);
  }
}
void pullSensors(){
  ir_sensors[0] = digitalRead(left);
  ir_sensors[1] = digitalRead(middle);
  ir_sensors[2] = digitalRead(right);

  line_sensors[0] = analogRead(LeftLineSensor);
  line_sensors[1] = analogRead(RightLIneSensor);

}