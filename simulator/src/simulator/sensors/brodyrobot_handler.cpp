#include <simulator/sensors/brodyrobot_handler.h>

BrodyRobotHandler::BrodyRobotHandler(std::shared_ptr<Robot> r, std::shared_ptr<Robot> o) {
    robot_ = r;
    opponent_ = o;
    dist_ = std::vector<std::shared_ptr<DistanceSensorJ>>();
    dist_.push_back(std::make_shared<DistanceSensorJ>(r, r->width_/2, r->length_/2, -10*M_PI/180, 3.6*M_PI/180, 150));
    dist_.push_back(std::make_shared<DistanceSensorJ>(r, r->width_/2, -r->length_/2, -5*M_PI/180, 3.6*M_PI/180, 150));
    dist_.push_back(std::make_shared<DistanceSensorJ>(r, -r->width_/2, r->length_/2, 0, 3.6*M_PI/180, 150));
    dist_.push_back(std::make_shared<DistanceSensorJ>(r, -r->width_/2, -r->length_/2, 0, 3.6*M_PI/180, 150));
    line_ = std::vector<std::shared_ptr<LineSensor>>();
    line_.push_back(std::make_shared<LineSensor>(r, 75, 200, 200, r->width_/2, r->length_/2));
    line_.push_back(std::make_shared<LineSensor>(r, 75, 200, 200, r->width_/2, -r->length_/2));    
    loc_ = std::make_shared<LocationSensor>(r, 0, 0);
}

SensorData BrodyRobotHandler::read(double duration) {
    SensorData s;
    auto d_buff = std::vector<double>();
    for (std::shared_ptr<DistanceSensorJ> d : dist_) {
        d_buff.push_back(d->read(opponent_));
    }
    s.dist_buffer_ = d_buff;
    auto l_buff = std::vector<int>();
    for (std::shared_ptr<LineSensor> l : line_) {
        l_buff.push_back(l->read());
    }
    s.line_buffer_ = l_buff;
    auto loc_buff = loc_->read();
   /* for (std::shared_ptr<LocationSensor> loc : loc_) {
        loc_buff.push_back(loc->read());
    }*/
    s.x_accel_ = loc_buff[0];
    s.y_accel_ = loc_buff[1];
    return s;
}