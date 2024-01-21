
// SlammyWhammy-For-Scummi
// by Xander Riddle
// Version 1.1
// Arduino IDE

// Desc: SlammyWhammy for Scummi... this works about as well as it could... yknow, cuz its Scummi :/

int rightLineSensor = 5;
int leftLineSensor = 7;
int beeeeeeep = 8;
int leftWheelBack = A1;
int leftWheelForward = A2;
int rightWheelBack = A3;
int rightWheelForward = A4;
int leftLidarSensor = A5;
int middleLidarSensor = A6;
int rightLidarSensor = A7;

// Threshold for how many times the line sensor has to read 0 before the slam loop breaks
// this is nessessary because the line sensor is really sensitive and stupid :)!
const int threshold = 10;

// Spins until it spots an enemy
void search() {
  Serial.println("Searching...");
  boolean enemySpotted = false;
  analogWrite(leftWheelForward, 1000);
  analogWrite(rightWheelBack, 1000);
  while (!enemySpotted) {
    if (analogRead(leftLidarSensor) == 0) {
      Serial.println("Enemy Spotted!");
      enemySpotted = true;
      analogWrite(rightWheelBack, 0);
      analogWrite(leftWheelForward, 0);
      analogWrite(rightWheelForward, 700);
      delay(400);
      analogWrite(rightWheelForward, 0);
    } else if (analogRead(middleLidarSensor) == 0) {
      Serial.println("Enemy Spotted!");
      enemySpotted = true;
      analogWrite(rightWheelBack, 0);
      analogWrite(leftWheelForward, 0);
    } else if (analogRead(rightLidarSensor) == 0) {
      Serial.println("Enemy Spotted!");
      enemySpotted = true;
      analogWrite(rightWheelBack, 0);
      analogWrite(leftWheelForward, 0);
      analogWrite(leftWheelForward, 700);
      delay(400);
      analogWrite(leftWheelForward, 0);
    }
  }
}

// Go forward until it hits a line
void slam() {
  analogWrite(leftWheelForward, 1000);
  analogWrite(rightWheelForward, 1000);
  Serial.print("SLAMING!!!");
  bool isOnLine = false;
  int rightLineCounter = 0;
  int leftLineCounter = 0;

  while (rightLineCounter < threshold && leftLineCounter < threshold) {
    if (digitalRead(rightLineSensor) == 0) {
        rightLineCounter++;
    } else {
        rightLineCounter = 0;  
    }

    if (digitalRead(leftLineSensor) == 0) {
        leftLineCounter++;
    } else {
        leftLineCounter = 0;
    }

    delay(1);
  }
  // Back up to reposition near the center
  analogWrite(leftWheelForward, 0);
  analogWrite(rightWheelForward, 0);
  analogWrite(leftWheelBack, 1000);
  analogWrite(rightWheelBack, 1000);
  delay(1000);
  analogWrite(leftWheelBack, 0);
  analogWrite(rightWheelBack, 0);
}

// Serial Monitor for testing
void setup() {
  Serial.begin(9600);
  while (!Serial.available());
}

// Slammy and Whammy
void loop() {
  search();
  slam();
}
