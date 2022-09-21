#include <Sensor.h>

class DistanceSensor : Sensor {
  double getInfo() {
    //custom logic :)
  }
  double angle; //0 to 2pi, 0 is forward from the robot, counterclockwise like a unit circle
  double lightRange; //the centimeter distance the lidar can shine -> The Dohyo's radius is 154cm
};