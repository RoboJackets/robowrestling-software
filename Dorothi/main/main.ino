#include "Adafruit_LIS3DH.h"
#include "Adafruit_VL53L0X.h"

//#include <Wire.h>

Adafruit_VL53L0X sensor1 = Adafruit_VL53L0X();
Adafruit_VL53L0X sensor2 = Adafruit_VL53L0X();

//SYSTEM_THREAD(ENABLED);
//SYSTEM_MODE(MANUAL);

Adafruit_LIS3DH sample;
int xAccel = 0;
int yAccel = 0;
int WKP = 1;

//Adafruit_LIS3DH accel(Wire, 0, WKP);

double time_x;
double prevTime_x;
double distance_x;
double velocity_x;
double time_y;
double prevTime_y;
double distance_y;
double velocity_y;

//Previous values
double prevVelocity_x;
double prevVelocity_y;
double prevAccel_x;
double prevAccel_y;
double tolerance = .1;
double maxRatio = 70;
double startingPos [2] = {0, 0}; //x and y coordinates

Adafruit_LIS3DH lis;

void accel_init() {
    lis = Adafruit_LIS3DH();
    delay(500);
    lis.setRange(LIS3DH_RANGE_4_G);
}

void setup()
{

  Serial.begin(9600);
  Wire.begin();

  // Serial.print("setup running");
  pinMode(A0, OUTPUT);
  pinMode(A1, OUTPUT);
  digitalWrite(A0, LOW);
  digitalWrite(A1, LOW);
  // //
  //
  // //
  pinMode(A0, INPUT);
  sensor1.begin();
  //sensor1.setTimeout(500);
  sensor1.setAddress(0x30);
  //
  pinMode(A1, INPUT);
  sensor2.begin();
  //sensor2.setTimeout(500);
  sensor2.setAddress(0x31);
  //
  // // Start continuous back-to-back mode (take readings as
  // // fast as possible).  To use continuous timed mode
  // // instead, provide a desired inter-measurement period in
  // // ms (e.g. sensor.startContinuous(100)).
  //sensor1.startContinuous();
  //sensor2.startContinuous();

  accel_init();
}

void loop() {

  VL53L0X_RangingMeasurementData_t measure;

  lis.read();
  xAccel = lis.x;
  yAccel = lis.y;

  time_x = millis();
  time_y = millis();
  double deltaT_x = time_x - prevTime_x;
  double deltaT_y = time_y - prevTime_y;
  double a_x = xAccel;
  double a_y = yAccel;

  double aMid_x = (a_x + prevAccel_x)/2.0;
  double aMid_y = (a_y + prevAccel_y)/2.0;

  velocity_x = aMid_x*deltaT_x + velocity_x;
  velocity_y = aMid_y*deltaT_y + velocity_y;

  double vMid_x = (velocity_x + prevVelocity_x)/2.0;
  double vMid_y = (velocity_y + prevVelocity_y)/2.0;

  distance_x = (0.5)*aMid_x*pow(deltaT_x, 2) + vMid_x*deltaT_x + distance_x;
  distance_y = (0.5)*aMid_y*pow(deltaT_y, 2) + vMid_y*deltaT_y + distance_y;

  double sensorLV = sensor2.rangingTest(&measure, false);
  double sensorMV = sensor1.rangingTest(&measure, false);
  Serial.print(sensorLV);
  Serial.print("   -----   ");
  Serial.print(sensorMV);
  Serial.println();
  double motorRV;
  double motorLV; //percentages
  // if (sensor1.timeoutOccurred()) { Serial.print(" TIMEOUT"); }
  // max is 2m away = 2000 mm
  // min = 30 mm
  //max ratio is 70
  //min ratio is .015; approx 0.0
  //ratio is left to right
  //if percentage is 1, turn all the way left
  //if percentage is 0, turn straight
  if (sensorLV > tolerance && sensorMV > tolerance) {
    motorLV = 0.0;
    motorRV = 0.25; //go slowly at first
  } else {
    double ratio = sensorLV / sensorMV;
    Serial.print("Ratio: ");
    Serial.print(ratio);
    Serial.println();
    double percentage = ratio / maxRatio;
    //max .5 to account for mid/left vs right/left
    //min = 0
    double adjustedValue = percentage / 2;
    motorLV = adjustedValue;
    motorRV = (1 - adjustedValue);
  }
  Serial.print("Right capacity: ");
  Serial.print(motorRV);
  Serial.println();
  Serial.print("Left capacity: ");
  Serial.print(motorLV);
  Serial.println();
  //Set the right motor to motorRV of max value
  //Set the left motor of motorLV of max value
  /* CODE INSERTED HERE */
  Serial.println();
  Serial.println();

  prevTime_x = time_x;
  prevTime_y = time_y;
  prevAccel_y = a_y;
  prevAccel_x = a_x;
  prevVelocity_x = velocity_x;
  prevVelocity_y = velocity_y;

}
