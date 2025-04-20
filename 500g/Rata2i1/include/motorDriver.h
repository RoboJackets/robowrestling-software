#ifndef MOTOR_DRIVER_H
#define MOTOR_DRIVER_H
class motorDriver {
    private:
        int speed;
        bool fwd;
        bool bwd;
    public:
        motorDriver();
        void setSpeed(int speed);
        void setDirection(bool direction);
        int getSpeed();
        bool getDirection();
};
#endif