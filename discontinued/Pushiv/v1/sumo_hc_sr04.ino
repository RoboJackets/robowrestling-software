#define leftEcho 2  // left Echo Pin
#define leftTrig 4  // left Trigger Pin
#define rightEcho 7 // right Echo Pin
#define rightTrig 6 // right Trigger Pin

int maximumRange = 200; // Maximum range needed
int minimumRange = 0; // Minimum range needed
long duration, leftDistance, rightDistance; // Duration used to calculate distance

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

void setup() {
 Serial.begin (9600);
 pinMode(leftTrig, OUTPUT);
 pinMode(leftEcho, INPUT);
 pinMode(rightTrig, OUTPUT);
 pinMode(rightEcho, INPUT);
}

void loop() {
 calcDistance();
 
 if (leftDistance >= maximumRange || leftDistance <= minimumRange){
  Serial.print("Left: ");
  Serial.println("-1");
 }
 else {
  Serial.print("Left: ");
  Serial.println(leftDistance);
 }

 if (rightDistance >= maximumRange || rightDistance <= minimumRange){
  Serial.print("Right: ");
  Serial.println("-1");
 }
 else {
  Serial.print("Right: ");
  Serial.println(rightDistance);
 }
 
 delay(50);
}
