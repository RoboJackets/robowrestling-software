#pragma once
#include <Arduino.h>

class Motors {
    public:
    void setup();

    void forward(int speed);
    void back(int speed);
    void rotateRight(int speed); //Both wheel turns
    void rotateLeft(int speed); //Both wheel turns
    void slowRight(int speed);  //Single wheel turns
    void slowLeft(int speed); //Single wheel turns
    void stop();

    void lineLeftTurn(int speed);
    void lineRightTurn(int speed);
    void lineMiddleTurn(int speed);
};