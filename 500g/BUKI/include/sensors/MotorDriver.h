#ifndef MOTOR_DRIVER_H_
#define MOTOR_DRIVER_H_

class MotorDriver {
    private:
        bool dir;
        unsigned int speed;
    public:
        MotorDriver();
        MotorDriver(int init_speed);
        MotorDriver(int init_speed, int init_dir);
        bool getDir();
        void setDir(bool);
        int getSpeed();
        void setSpeed(int);
};

#endif