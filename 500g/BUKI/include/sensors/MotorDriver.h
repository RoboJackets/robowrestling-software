#ifndef MOTOR_DRIVER_H_
#define MOTOR_DRIVER_H_

class MotorDriver {
    private:                                    // attributes
        bool dir;               
        unsigned int speed;
    public:                                     // methods
        MotorDriver();      // constructer
        MotorDriver(int init_speed);        // constructer
        MotorDriver(int init_speed, int init_dir);      // constructer
        bool getDir();
        void setDir(bool);
        int getSpeed();
        void setSpeed(int);
};

#endif