#include <simulator/sensors/gps_sensor.h>

GPSSensor::GPSSensor(std::shared_ptr<Robot> robot, double sens_x, double sens_y, double sens_angle, double cone_angle, double cone_length) {
    robot_ = robot;
    sens_x_ = sens_x;
    sens_y_ = sens_y;
    sens_angle_ = sens_angle;
    cone_angle_ = cone_angle;
    cone_length_ = cone_length;
}

/*
    Find closest corner to robot
        edge parallel
    Find lines adjecent to corner
        keeping the line function within its limits
        check:
            min (x1, x2) <= finalx <= max (x1, x2)
            min (y1, y2) <= finaly <= max (y1, y2)
    Average findings together
*/
double GPSSensor::read(std::shared_ptr<Robot> target) {
    std::vector<pdd> corners = target->corners(); // Vectors[], Pairs .first .second for fields
    int minCorner = 0; // Use (minCorner +- 1) % 4 to find adjascents
    double distCorner = get_distance(corners[0]);
    for (int i = 1; i < 4; i++) { // Finds clostest corner to the sensor
        if (get_distance(corners[i]) < distCorner) {
            minCorner = i;
            distCorner = get_distance(corners[i]);
        }
    }

    pdd sensor_origin;
    pdd sensor_max;
    pdd intersection;
    bool is_on_robot_1 = false;
    bool is_on_robot_2 = false;
    double average;
    int total_rays = 7; // Keep odd
    double weights[] = {.05, .10, .20, .30, .20, .10, .05}; // Change based on #rays

    sensor_origin.first = (cos(robot_->angle_) * sens_x_ - sin(robot_->angle_) * sens_y_) + robot_->x_pos_;
    sensor_origin.second = (cos(robot_->angle_) * sens_y_ + sin(robot_->angle_) * sens_x_) + robot_->y_pos_;

    for (int i = -total_rays / 2; i <= total_rays / 2; i++) {
        is_on_robot_1 = false;
        is_on_robot_2 = false;
        sensor_origin.first = (cos(robot_->angle_) * sens_x_ - sin(robot_->angle_) * sens_y_) + robot_->x_pos_;
        sensor_origin.second = (cos(robot_->angle_) * sens_y_ + sin(robot_->angle_) * sens_x_) + robot_->y_pos_;
        sensor_max.first = sensor_origin.first + cone_length_ * (cos(robot_->angle_ + sens_angle_ + i * cone_angle_ / (total_rays - 1)));
        sensor_max.second = sensor_origin.second + cone_length_ * (sin(robot_->angle_ + sens_angle_ + i * cone_angle_ / (total_rays - 1)));

        
        intersection = lineLineIntersection(sensor_origin, sensor_max, corners[minCorner], corners[(minCorner + 1) % 4]);
        if (intersection.first >= std::min(sensor_origin.first, sensor_max.first)
            && intersection.first <= std::max(sensor_origin.first, sensor_max.first)) {

            is_on_robot_1 = std::min(corners[minCorner].first, corners[(minCorner + 1) % 4].first) <= intersection.first 
                && intersection.first <= std::max(corners[minCorner].first, corners[(minCorner + 1) % 4].first)
                && std::min(corners[minCorner].second, corners[(minCorner + 1) % 4].second) <= intersection.second 
                && intersection.second <= std::max(corners[minCorner].second, corners[(minCorner + 1) % 4].second);

            if (is_on_robot_1) {
                average += get_distance(intersection) * weights[i + total_rays/2];
            }
        }

        intersection = lineLineIntersection(sensor_origin, sensor_max, corners[minCorner], corners[(minCorner - 1) % 4]);
        if (intersection.first >= std::min(sensor_origin.first, sensor_max.first)
            && intersection.first <= std::max(sensor_origin.first, sensor_max.first)) {

            is_on_robot_2 = std::min(corners[minCorner].first, corners[(minCorner - 1) % 4].first) <= intersection.first 
                && intersection.first <= std::max(corners[minCorner].first, corners[(minCorner - 1) % 4].first)
                && std::min(corners[minCorner].second, corners[(minCorner - 1) % 4].second) <= intersection.second 
                && intersection.second <= std::max(corners[minCorner].second, corners[(minCorner - 1) % 4].second);

            if (is_on_robot_2 && !is_on_robot_1) {
                average += get_distance(intersection) * weights[i + total_rays/2];
            }
        }

        if (!is_on_robot_1 && !is_on_robot_2) {
            average += cone_length_ * weights[i + total_rays/2];
        }
    }

    return average;
}

double GPSSensor::get_distance(pdd point) {
    double dist_x = point.first - ((cos(robot_->angle_) * sens_x_ - sin(robot_->angle_) * sens_y_) + robot_->x_pos_);
    double dist_y = point.second - ((cos(robot_->angle_) * sens_y_ + sin(robot_->angle_) * sens_x_) + robot_->y_pos_);
    return sqrt(pow(dist_x, 2) + pow(dist_y, 2));
}

pdd lineLineIntersection(pdd A, pdd B, pdd C, pdd D) 
{ 
    // Line AB represented as a1x + b1y = c1 
    double a1 = B.second - A.second; 
    double b1 = A.first - B.first; 
    double c1 = a1*(A.first) + b1*(A.second); 
  
    // Line CD represented as a2x + b2y = c2 
    double a2 = D.second - C.second; 
    double b2 = C.first - D.first; 
    double c2 = a2*(C.first)+ b2*(C.second); 
  
    double determinant = a1*b2 - a2*b1; 
  
    if (determinant == 0) 
    { 
        // The lines are parallel. This is simplified 
        // by returning a pair of -1
        return std::make_pair(-1, -1);
    } 
    else
    { 
        double x = (b2*c1 - b1*c2)/determinant; 
        double y = (a1*c2 - a2*c1)/determinant; 
        return std::make_pair(x, y);
    } 
}