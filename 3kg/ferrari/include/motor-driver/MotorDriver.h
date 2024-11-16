#ifndef MOTOR_DRIVER_H
#define MOTOR_DRIVER_H
class MotorDriver {
    private:
        int speed;
    public:
        MotorDriver();
        MotorDriver(int speed);
        void set_speed(int speed);
        int get_speed();
};
#endif