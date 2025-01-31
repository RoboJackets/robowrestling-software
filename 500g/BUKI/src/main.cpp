#include <Arduino.h>

#define Lside 12
#define Lsensor 8
#define Rside 2
#define Rsensor 4
#define MSensor 7
#define StartMod 10

#define Rpos 6
#define Rneg 11
#define Lpos 3
#define Lneg 5
#define switch1 A6
#define switch2 A7
void line();
void stop();
void turnLeft(double);
void turnRight(double); 
void back(double);
void forward(double);
void rotateRight(double);
void rotateLeft(double);

void setup() {
  pinMode(Rpos, OUTPUT); 
  pinMode(Rneg, OUTPUT);
  pinMode(Lpos, OUTPUT); 
  pinMode(Lneg, OUTPUT);
  pinMode(StartMod, INPUT);

  pinMode(switch1, INPUT);
  pinMode(switch2, INPUT);
  Serial.begin(9600);
}

void loop() {
  if(digitalRead(MSensor))
    forward(100);
  else 
    stop(); 

}
void stop() {
  analogWrite(Rpos, 0);
  analogWrite(Rneg, 0);
  analogWrite(Lpos, 0);
  analogWrite(Lneg, 0);
}
void forward(double speed) {
  analogWrite(Rpos, speed+15);
  analogWrite(Rneg, 0);
  analogWrite(Lpos, speed);
  analogWrite(Lneg, 0);
}
void back(double speed) {
  analogWrite(Rpos, 0);
  analogWrite(Rneg, speed+15);
  analogWrite(Lpos, 0);
  analogWrite(Lneg, speed);
}
void rotateRight(double speed) {
  analogWrite(Rpos, 0);
  analogWrite(Rneg, speed+10);
  analogWrite(Lpos, speed);
  analogWrite(Lneg, 0);
}
void rotateLeft(double speed) {
  analogWrite(Rpos, speed+10);
  analogWrite(Rneg, 0);
  analogWrite(Lpos, 0);
  analogWrite(Lneg, speed);
}
void turnRight(double speed) {
  analogWrite(Rpos, 0);
  analogWrite(Rneg, 0);
  analogWrite(Lpos, speed);
  analogWrite(Lneg, 0);
}
void turnLeft(double speed) {
  analogWrite(Rpos, speed+10);
  analogWrite(Rneg, 0);
  analogWrite(Lpos, 0);
  analogWrite(Lneg, 0);
}