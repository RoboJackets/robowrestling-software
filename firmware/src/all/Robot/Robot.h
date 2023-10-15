#ifndef ROBOT_H
#define ROBOT_H

#include <vector>
#include "RobotState.h"
#include "../Sensors/Sensor.h"

class Robot {
    protected:
        std::vector<Sensor*> _sensors;
        RobotState _state;

    public:
        Robot() {}
        virtual void UpdateState() = 0;

        inline void UpdateSensors() {
            for (Sensor *sensor : _sensors) {
                sensor->Poll();
            }
        }

        const RobotState& GetRobotState() {
            return _state;
        }
};

#endif
