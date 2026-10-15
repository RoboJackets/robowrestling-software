#ifndef ACCELEROMETER_H
#define ACCELEROMETER_H

// TODO: replace everything with vector3's

class Accelerometer {
private:
    int x;
    int y;
    int z;
public:
    void setAcceleration(int xValue, int yValue, int zValue);
    int getX();
    int getY();
    int getZ();
};

class Velocity {
private:
    int x;
    int y;
    int z;
public:
    void setVelocity(int xValue, int yValue, int zValue);
    int getX();
    int getY();
    int getZ();
};

#endif