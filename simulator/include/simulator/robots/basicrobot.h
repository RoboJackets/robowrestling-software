#ifndef basicrobot_h
#define basicrobot_h

#include <simulator/robots/robot.h>
#include <strategy/slammywhammy.h>

class BasicRobot: public Robot { //basic robot for testing purposes
	public: 
        BasicRobot(double x_pos, double y_pos, double angle);

        std::vector<std::pair<double, double>> corners();
};

#endif