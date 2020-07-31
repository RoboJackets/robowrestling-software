#ifndef robot_h
#define robot_h

class Robot { //abstract class of a robot
	public:
		double x_pos; //x position relative to the center of the dohyo
		double y_pos; //y position relative to the center of the dohyo
		double angle; //how much the robot is rotated from 0-359 with 0 being "north"
		
		double width; //width of robot used for collision and ring out calculations
		double length; //length of robot used for collision and ring out calculations
		
		double velocity; //robot's current velocity used for collision calculations. m/s?

		//virtual void drive(int left, int right) = 0; //used to update position of robot in a similar way to that of the physical bots
		//virtual void get_sensor_data() = 0; //retrieve "sensor" data for use in strategy
};
#endif