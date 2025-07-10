#ifndef MOTOR_DRIVER_H_
#define MOTOR_DRIVER_H_

class MotorDriver {
    private:                                    // attributes
        int dir;               
        unsigned int speed;
    public:                                     // methods
        MotorDriver();      // constructer
        MotorDriver(int init_speed);        // constructer
        MotorDriver(int init_speed, int init_dir);      // constructer
        int getDir();
        void setDir(int);
        int getSpeed();
        void setSpeed(int);
};

#endif