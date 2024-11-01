#pragma once
#include "../common.h"

class Robot {
    public:
        // telemetry
        bool atBoundary;
        float orientation[3];
        bool irValues[5];
        bool startModActivated;

        // robot config
        Flags flags;
        MotorDriver rightMotorDriver;
        MotorDriver leftMotorDriver;
        
        IMU imu;
        IRSensor leftIR;
        IRSensor midLeftIR;
        IRSensor midIR;
        IRSensor midRightIR;
        IRSensor rightIR;
        LineSensor leftLineSensor;
        LineSensor rightLineSensor;

        DipSwitch dipSwitch;

        StartModule startModule;

        Robot();
        void createIRSensors(uint8_t pins[5]);
        void createIMU();
        void createLineSensors(uint8_t pins[2]);
        void createMotors(uint8_t leftMotorPins[2], uint8_t rightMotorPins[2]);
        void createFlags(uint8_t pin);
        void createStartModule(uint8_t pin);
        void createDipSwitch(uint8_t pin1, uint8_t pin2);
        void updateState();
        
        bool checkBoundary();
        const bool* getIRValues();
        const float* getPose();
        bool getStartModActivated();

        void moveForwards(int speed);
        void moveBackwards(int speed);
        void moveForwards(int speed, int time);
        void moveBackwards(int speed, int time);

        void turnMove(int speedLeft, int speedRight);

        void turnLeftNoGyro(int speed, int time);
        void turnRightNoGyro(int speed, int time);
        
        void brakeHigh();


        
};