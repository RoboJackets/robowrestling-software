#include <Arduino.h>


/*[env:LGT8F328P]
platform = lgt8f
board = LGT8F328P
framework = arduino 
*/

void setup() {
  RobotState monki_see;
  RobotAction monki_do;
  WorldState monki_world;
  StartModule monki_start;
  IMU monki_imu;
  LineSensor monki_line_sensor;
  IrSensor monki_ir_sensor;
  MotorDriver monki_motor_driver;
  // Initialize the serial communication
  Serial.begin(9600);
  // Initialize the motors
  
}

void loop() {
}
