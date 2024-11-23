#ifndef MOTOR_DRIVER_H
#define MOTOR_DRIVER_H
class MotorDriver {
    private:
        int speed;
    public:
        MotorDriver();
        MotorDriver(int speed);
        void setSpeed(int speed);
        int getSpeed();
};
#endif