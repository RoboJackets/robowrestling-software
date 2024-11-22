#include "Accelerometer.h"

void Accelerometer::setAcceleration(int xValue, int yValue, int zValue) {
    x = xValue;
    y = yValue;
    z = zValue;
}

int Accelerometer::getX() {
    return x;
}

int Accelerometer::getY() {
    return y;
}

int Accelerometer::getZ() {
    return z;
}

void Velocity::setVelocity(int xValue, int yValue, int zValue) {
    x = xValue;
    y = yValue;
    z = zValue;
}

int Velocity::getX() {
    return x;
}

int Velocity::getY() {
    return y;
}

int Velocity::getZ() {
    return z;
}