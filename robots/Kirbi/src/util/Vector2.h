#ifndef VECTOR2_H
#define VECTOR2_H

#include <tuple>

template<typename T> 
class Vector2 {
private: 
    T _x; 
    T _y; 

public: 

    Vector2(T x, T y): _x(x), _y(y) {

    }

    T GetX() {
        return _x; 
    }

    T GetY() {
        return _y; 
    }
}; 

#endif 