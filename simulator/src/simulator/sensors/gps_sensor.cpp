#include <simulator/sensors/gps_sensor.h>

GPSSensor::GPSSensor(std::shared_ptr<Robot> robot, double sens_x, double sens_y) {
    robot_ = robot;
        sens_x_ = sens_x;
    sens_y_ = sens_y;
}

/*
    We just want to get the robot's current x and current y
    so i dont really think we need to read
*/
// double GPSSensor::read(std::shared_ptr<Robot> target) {
    
 
// }

double GPSSensor::get_y_pos() {
    double y_position = robot_->y_pos_;
    return y_position;
}

double GPSSensor::get_x_pos() {
    double x_position = robot_->x_pos_;
    return x_position;
}

// pdd lineLineIntersection(pdd A, pdd B, pdd C, pdd D) 
// { 
//     // Line AB represented as a1x + b1y = c1 
//     double a1 = B.second - A.second; 
//     double b1 = A.first - B.first; 
//     double c1 = a1*(A.first) + b1*(A.second); 
  
//     // Line CD represented as a2x + b2y = c2 
//     double a2 = D.second - C.second; 
//     double b2 = C.first - D.first; 
//     double c2 = a2*(C.first)+ b2*(C.second); 
  
//     double determinant = a1*b2 - a2*b1; 
  
//     if (determinant == 0) 
//     { 
//         // The lines are parallel. This is simplified 
//         // by returning a pair of -1
//         return std::make_pair(-1, -1);
//     } 
//     else
//     { 
//         double x = (b2*c1 - b1*c2)/determinant; 
//         double y = (a1*c2 - a2*c1)/determinant; 
//         return std::make_pair(x, y);
//     } 
// }