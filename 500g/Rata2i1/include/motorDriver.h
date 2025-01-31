#ifndef MOTOR_DRIVER_H
#define MOTOR_DRIVER_H
class motorDriver {
    private:
        int speed;
        int direction;
    public:
        motorDriver();
        void setSpeed(int speed);
        void setDirection(int direction);
        void stop();
        int getSpeed();
        bool getDirection();
};
#endif