#include "Adafruit_VL53L0X.h"

Adafruit_VL53L0X left_sensor = Adafruit_VL53L0X();
Adafruit_VL53L0X front_sensor = Adafruit_VL53L0X();

double tolerance = .1; //yes
double max_ratio = 70; //i agree

void setup()
{

  Serial.begin(9600);
  Wire.begin();

  // Serial.print("setup running");
  pinMode(A0, OUTPUT);
  pinMode(A1, OUTPUT);
  digitalWrite(A0, LOW);
  digitalWrite(A1, LOW);

  pinMode(A0, INPUT);
  left_sensor.begin();
  left_sensor.setAddress(0x30);
  
  pinMode(A1, INPUT);
  front_sensor.begin();
  front_sensor.setAddress(0x31);

}

void loop() {

  VL53L0X_RangingMeasurementData_t measure;

  double sensor_left_val = front_sensor.rangingTest(&measure, false);
  double sensor_front_val = left_sensor.rangingTest(&measure, false);
  Serial.print(sensor_left_val);
  Serial.print("   -----   ");
  Serial.print(sensor_front_val);
  Serial.println();
  double motor_right_val;
  double motor_left_val; //percentages
  // if (left_sensor.timeoutOccurred()) { Serial.print(" TIMEOUT"); }
  // max is 2m away = 2000 mm
  // min = 30 mm
  //max ratio is 70
  //min ratio is .015; approx 0.0
  //ratio is left to right
  //if percentage is 1, turn all the way left
  //if percentage is 0, turn straight
  if (sensor_left_val > tolerance && sensor_front_val > tolerance) {
    motor_left_val = -0.25;
    motor_right_val = 0.25; //go slowly at first
  } else {
    double ratio = sensor_left_val / sensor_front_val;
    Serial.print("Ratio: ");
    Serial.print(ratio);
    Serial.println();
    double percentage = ratio / max_ratio;
    //max .5 to account for mid/left vs right/left
    //min = 0
    double adjusted_val = percentage / 2;
    motor_left_val = adjusted_val;
    motor_right_val = (1 - adjusted_val);
  }
  Serial.print("Right capacity: ");
  Serial.print(motor_right_val);
  Serial.println();
  Serial.print("Left capacity: ");
  Serial.print(motor_left_val);
  Serial.println();
  //Set the right motor to motor_right_val of max value
  //Set the left motor of motor_left_val of max value
  /* CODE INSERTED HERE */
  Serial.println();
  Serial.println();

}
