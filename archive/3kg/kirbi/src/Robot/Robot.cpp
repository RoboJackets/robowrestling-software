#include "Robot/Robot.h"

bool Robot::UpdateSensors() {
    for (Sensor* sensor : _sensors) {
        sensor -> Poll();
    }

    UpdateState();
    return true;
}

const RobotState& Robot::GetCurrentState() {
    return _state;
}
