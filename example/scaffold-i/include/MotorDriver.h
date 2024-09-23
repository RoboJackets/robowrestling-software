#ifndef MOTORDRIVER_H
#define MOTORDRIVER_H

class MotorDriver{
    private:
        int input;
        int speed;

    public:
        MotorDriver();
        MotorDriver(int input, int speed);
        int getInput();
        void setInput(int input);
        int getSpeed();
        void setSpeed(int speed);
};

#endif