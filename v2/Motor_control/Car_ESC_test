// Testing a HK CAR ESC

#include <Servo.h>  ;  // create servo object to control a servo 

Servo carESC;

void setup() 
{ 
  Serial.begin(9600);
  carESC.attach(11);  
  carESC.writeMicroseconds(1500);
  delay(5000);
} 

//fwd and rev min delay
//increasing speed by steps w delay

//note the delay will likely decrease w/ the gearbox

void loop() {
  Serial.print("Forward");
  Serial.print("Time: ");
  carESC.writeMicroseconds(1630);
  Serial.println(millis());
  delay(1000);//full speed

  Serial.println("Stop");
  carESC.writeMicroseconds(1500);
  delay(250);
  
  Serial.print("Reverse, ");
  Serial.print("Time: ");
  carESC.writeMicroseconds(1380);
  Serial.println(millis());
  delay(4000);

  Serial.print("Stop");
  Serial.print("Time: ");
  carESC.writeMicroseconds(1500);
  Serial.println(millis());
  delay(1000);

  while(1){}
}
