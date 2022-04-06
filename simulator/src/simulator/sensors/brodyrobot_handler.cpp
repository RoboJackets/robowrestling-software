#include <simulator/sensors/brodyrobot_handler.h>

BrodyRobotHandler::BrodyRobotHandler(std::shared_ptr<Robot> r, std::shared_ptr<Robot> o) {
    robot_ = r;
    opponent_ = o;
    dist_ = std::vector<std::shared_ptr<DistanceSensorJ>>();
    dist_.push_back(std::make_shared<DistanceSensorJ>(r, r->width_/2 - 3, r->length_/2, -10*M_PI/180, 3.6*M_PI/180, 150));
    dist_.push_back(std::make_shared<DistanceSensorJ>(r, r->width_/2 - 3, r->length_/4, -5*M_PI/180, 3.6*M_PI/180, 150));
    dist_.push_back(std::make_shared<DistanceSensorJ>(r, r->width_/2 - 3, r->length_/8, 0, 3.6*M_PI/180, 150));
    dist_.push_back(std::make_shared<DistanceSensorJ>(r, r->width_/2 - 3, -r->length_/8, 0, 3.6*M_PI/180, 150));
    line_ = std::vector<std::shared_ptr<LineSensor>>();
    line_.push_back(std::make_shared<LineSensor>(r, 75, 200, 200, r->width_/2, r->length_/2));
    line_.push_back(std::make_shared<LineSensor>(r, 75, 200, 200, r->width_/2, -r->length_/2));    
    loc_ = std::vector<std::shared_ptr<LocactionSensor>>();
    loc_.push_back(std::make_shared<LocactionSensor>(r));
}