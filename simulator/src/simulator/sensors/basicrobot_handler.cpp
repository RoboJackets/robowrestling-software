#include <simulator/sensors/basicrobot_handler.h>

BasicRobotHandler::BasicRobotHandler(std::shared_ptr<Robot> r) {
    robot_ = r;
    dist_ = std::make_unique<DistanceSensor>(r, 0, 0, 0, M_PI/16, 200);
    imu_ = std::make_unique<IMU>(r);
}

std::vector<double> BasicRobotHandler::read(double duration) {
    std::vector<double> ret;
    auto imu_readings = imu_->read(duration);
    ret.insert(ret.end(), imu_readings.begin(), imu_readings.end());
    return ret;
}

std::vector<double> BasicRobotHandler::read(double duration, std::shared_ptr<Robot> target) {
    std::vector<double> ret = this->read(duration);
    ret.push_back(dist_->read(target));
    return ret;
}