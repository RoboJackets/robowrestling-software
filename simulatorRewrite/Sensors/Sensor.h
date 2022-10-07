#include <pair>

class Sensor {
  /**
   * @brief Get the Info object
   * 
   * @param robotPos the position of the robot in meters defined from the bottom left
   * @return double ??
   */
  virtual double getInfo(std::pair<double, double> robotPos) = 0;
  // 0 is the center of the robot
  //location relative to placement on robot
  double x;
  double y; 
};