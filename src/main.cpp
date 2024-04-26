#include <Arduino.h>


#define PIN_MOTOR_LEFT_FORWARD_PIN 4
#define PIN_MOTOR_LEFT_REVERSE_PIN 3 

#define PIN_MOTOR_RIGHT_FORWARD_PIN 6
#define PIN_MOTOR_RIGHT_REVERSE_PIN 5

#define PIN_JS40F_LEFT_PIN 23 
#define PIN_JS40F_MID_LEFT_PIN 22
#define PIN_JS40F_MID 21
#define PIN_JS40F_MID_RIGHT 20
#define PIN_JS40F_RIGHT 19

#define LINE_SENSOR_LEFT 18 
#define LINE_SENSOR_RIGHT 17 

#define START_MODULE 16

#define LINE_SENSOR_THRESHOLD 80


// put function declarations here:
void search();
void moveBackwards();
void boundaryDetectedManuever();
void stop();
void boundaryDetectedTurn();

void detectionStuff();
bool isLineDetected();

  void turn90left();
  void turn90right();



bool isLineDetected() {
  return analogRead(LINE_SENSOR_LEFT) < LINE_SENSOR_THRESHOLD || analogRead(LINE_SENSOR_RIGHT) < LINE_SENSOR_THRESHOLD;
}


bool irSensorValues[] = {false, false, false, false, false};



void setup() {
  // put your setup code here, to run once:
  pinMode(PIN_MOTOR_LEFT_FORWARD_PIN, OUTPUT);
  pinMode(PIN_MOTOR_LEFT_REVERSE_PIN, OUTPUT);
  pinMode(PIN_MOTOR_RIGHT_FORWARD_PIN, OUTPUT);
  pinMode(PIN_MOTOR_RIGHT_REVERSE_PIN, OUTPUT);

  pinMode(PIN_JS40F_LEFT_PIN, INPUT);
  pinMode(PIN_JS40F_MID_LEFT_PIN, INPUT);
  pinMode(PIN_JS40F_MID, INPUT);
  pinMode(PIN_JS40F_MID_RIGHT, INPUT);
  pinMode(PIN_JS40F_RIGHT, INPUT);

  pinMode(LINE_SENSOR_LEFT, INPUT);
  pinMode(LINE_SENSOR_RIGHT, INPUT);

  pinMode(START_MODULE, INPUT);

  Serial.begin(9600);

  delay(3000);
}

void fullFowards() {
  analogWrite(PIN_MOTOR_LEFT_FORWARD_PIN, 255);
  analogWrite(PIN_MOTOR_LEFT_REVERSE_PIN, 0);
  analogWrite(PIN_MOTOR_RIGHT_FORWARD_PIN, 255);
  analogWrite(PIN_MOTOR_RIGHT_REVERSE_PIN, 0);

}

void slowerForwards() {
  analogWrite(PIN_MOTOR_LEFT_FORWARD_PIN, 90);
  analogWrite(PIN_MOTOR_LEFT_REVERSE_PIN, 0);
  analogWrite(PIN_MOTOR_RIGHT_FORWARD_PIN, 90);
  analogWrite(PIN_MOTOR_RIGHT_REVERSE_PIN, 0);


}

void loop() {


  bool leftDetected = digitalRead(PIN_JS40F_LEFT_PIN);
  bool midLeftDetected = digitalRead(PIN_JS40F_MID_LEFT_PIN);
  bool midDetected = digitalRead(PIN_JS40F_MID);
  bool midRightDetected = digitalRead(PIN_JS40F_MID_RIGHT);
  bool rightDetected = digitalRead(PIN_JS40F_RIGHT);
  bool startModuleActivated = digitalRead(START_MODULE);

  Serial.begin(9600);
  Serial.println(analogRead(LINE_SENSOR_LEFT));




  if (startModuleActivated) {

      if (midDetected && !midLeftDetected && !midRightDetected) {
          if (isLineDetected() == true) {
            detectionStuff();
          } else {
            fullFowards();
          }
      } else if (midDetected && midLeftDetected && midRightDetected) {
              if (isLineDetected() == true) {
              detectionStuff();
          } else {
            fullFowards();
          
          }
      } else if (midDetected && midLeftDetected && !midRightDetected) {
        if (isLineDetected() == true) {
              detectionStuff();
          } else {
            analogWrite(PIN_MOTOR_LEFT_FORWARD_PIN, 0);
            analogWrite(PIN_MOTOR_LEFT_REVERSE_PIN,35);
            analogWrite(PIN_MOTOR_RIGHT_FORWARD_PIN, 35);
            analogWrite(PIN_MOTOR_RIGHT_REVERSE_PIN, 0);
          }
      } else if (midDetected && !midLeftDetected && midRightDetected) {
        if (isLineDetected() == true) {
              detectionStuff();
          } else {
            analogWrite(PIN_MOTOR_LEFT_FORWARD_PIN, 35);
            analogWrite(PIN_MOTOR_LEFT_REVERSE_PIN, 0);
            analogWrite(PIN_MOTOR_RIGHT_FORWARD_PIN, 0);
            analogWrite(PIN_MOTOR_RIGHT_REVERSE_PIN, 35);
          }
      } else if (!midDetected && midLeftDetected && !midRightDetected) {
            if (isLineDetected() == true)
            {
              detectionStuff();
            } else {
              analogWrite(PIN_MOTOR_LEFT_FORWARD_PIN, 0);
              analogWrite(PIN_MOTOR_LEFT_REVERSE_PIN, 75);
              analogWrite(PIN_MOTOR_RIGHT_FORWARD_PIN, 75);
              analogWrite(PIN_MOTOR_RIGHT_REVERSE_PIN, 0);
            }
      } else if (!midDetected && !midLeftDetected && midRightDetected) {
            if (isLineDetected() == true)
            {
              detectionStuff();
            } else {
              analogWrite(PIN_MOTOR_LEFT_FORWARD_PIN, 75);
              analogWrite(PIN_MOTOR_LEFT_REVERSE_PIN, 0);
              analogWrite(PIN_MOTOR_RIGHT_FORWARD_PIN, 0);
              analogWrite(PIN_MOTOR_RIGHT_REVERSE_PIN, 75);
            }
      } else if (rightDetected) {
                if (isLineDetected() == true)
            {
              detectionStuff();
            } else {
          turn90right();
            }
      } else if (leftDetected) {
          if (isLineDetected() == true)
            {
              detectionStuff();
            } else {
            turn90left();
          }

      } else {
              // regular search
          if (isLineDetected() == true)
          {
            detectionStuff();
          } else {
            slowerForwards();
          }
      }
  } else {
    stop();
  }
}




void detectionStuff() {
  moveBackwards();
  boundaryDetectedTurn();
}

// put function definitions here:

void moveBackwards() {
    analogWrite(PIN_MOTOR_LEFT_FORWARD_PIN, 0);
  analogWrite(PIN_MOTOR_LEFT_REVERSE_PIN, 255);
  analogWrite(PIN_MOTOR_RIGHT_FORWARD_PIN, 0);
  analogWrite(PIN_MOTOR_RIGHT_REVERSE_PIN, 255);

  delay(200);
  stop();
}

void stop() {
  analogWrite(PIN_MOTOR_LEFT_FORWARD_PIN, 255);
  analogWrite(PIN_MOTOR_LEFT_REVERSE_PIN, 255);
  analogWrite(PIN_MOTOR_RIGHT_FORWARD_PIN, 255);
  analogWrite(PIN_MOTOR_RIGHT_REVERSE_PIN, 255);
}

void boundaryDetectedManuever() {
  // move backwards
  analogWrite(PIN_MOTOR_LEFT_FORWARD_PIN, 0);
  analogWrite(PIN_MOTOR_LEFT_REVERSE_PIN, 100);
  analogWrite(PIN_MOTOR_RIGHT_FORWARD_PIN, 0);
  analogWrite(PIN_MOTOR_RIGHT_REVERSE_PIN, 100);

  delay(500);

}

void boundaryDetectedTurn() {
  analogWrite(PIN_MOTOR_LEFT_FORWARD_PIN, 255);
  analogWrite(PIN_MOTOR_LEFT_REVERSE_PIN, 0);
  analogWrite(PIN_MOTOR_RIGHT_FORWARD_PIN, 0);
  analogWrite(PIN_MOTOR_RIGHT_REVERSE_PIN, 255);

  delay(150);

  stop();
}



void turn90left() {
  analogWrite(PIN_MOTOR_LEFT_FORWARD_PIN, 0);
  analogWrite(PIN_MOTOR_LEFT_REVERSE_PIN, 255);
  analogWrite(PIN_MOTOR_RIGHT_FORWARD_PIN, 255);
  analogWrite(PIN_MOTOR_RIGHT_REVERSE_PIN, 0);

  delay(150);

  stop();
}

void turn90right() {
  analogWrite(PIN_MOTOR_LEFT_FORWARD_PIN, 255);
  analogWrite(PIN_MOTOR_LEFT_REVERSE_PIN, 0);
  analogWrite(PIN_MOTOR_RIGHT_FORWARD_PIN, 0);
  analogWrite(PIN_MOTOR_RIGHT_REVERSE_PIN, 255);

  delay(150);

  stop();
}
