#ifndef MOTOR_DRIVER_H
#define MOTOR_DRIVER_H

class motor_driver {
    private:
        bool direction;
        int speed;
    public:
        motor_driver();
        motor_driver(bool direction, int speed);
        void set_direction(bool new_direction);
        void set_speed(int new_speed);
        bool get_direction();
        int get_speed();
};
#endif