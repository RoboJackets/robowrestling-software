#ifndef VECTOR_2_H
#define VECTOR_2_H

template<typename T>
class Vector2 {
private:
    T x_;
    T y_;
public:
    Vector2(T x, T y) : x_(x), y_(y) { } 
    T getX() { return x_ }
    T getY() { return y_ }
};

#endif