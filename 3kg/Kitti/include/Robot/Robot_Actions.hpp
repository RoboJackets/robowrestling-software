#ifndef ROBOT_ACTIONS_HPP
#define ROBOT_ACTIONS_HPP

class RobotActions {
    private:
        int motors[2]; // motors = {Left, Right}
    public:
        RobotActions();
        void brake();
        void drive_forward(int speed);
        void drive_backward(int speed);
        void drive_left(int speed);
        void drive_right(int speed);
        int get_left_velocity();
        int get_right_velocity();
};

#endif // ROBOT_ACTIONS_HPP