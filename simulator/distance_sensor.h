#ifndef distance_sensor_h
#define distance_sensor_h

#include "robot.h"
#include "abstract_distance_sensor.h"

class DistanceSensor : public AbstractDistanceSensor {

    public: 
        DistanceSensor(Robot* robot, int x, int y, int angle) {
            setRobot(robot);
            setSensorPosition(x, y, angle);
        };

        /*
        returns distance from a specified Robot
        */
        int read(Robot* robot) {
            return -1;
        }
};

#endif