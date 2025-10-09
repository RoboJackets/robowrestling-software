#ifndef MOTORACTIONS_H
#define MOTORACTIONS_H

class motorActions {
public:


    motorActions(int* motors, int* irSensors, int* lineSensors);

    void writeMotors();
    void drive(); 
    void driveForward(int speed); 
    void driveBackward(int speed); 
    void spinLeft(int speed); 
    void spinRight(int speed); 
    void customDrive(int rightSpeed, int leftSpeed);
    void stop();
private:
    int* motors;
    int* lineSensors;   // pointer to 2 line sensors
    int* irSensors;     // pointer to 3 IR sensors

};

#endif
