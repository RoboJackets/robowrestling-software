#include "simulator/physics/Vector2f.h"
#include <iostream>
Vector2f::Vector2f(): x(0.0), y(0.0) {}

Vector2f::Vector2f(double x, double y): x(x), y(y) {}



double Vector2f::CrossProduct(const Vector2f &u, const Vector2f &v) {
    
    return u.x * v.y - u.y * v.x; 
}

double Vector2f::DotProduct(const Vector2f &u, const Vector2f &v) {
    return u.x * v.x + u.y * v.y; 
}


Vector2f Vector2f::Scale(const double factor) {
    return Vector2f(x * factor, y * factor);  
}

double Vector2f::Norm() {
    return std::sqrt(std::pow(x,2) + std::pow(y,2)); 
}

Vector2f Vector2f::Normalize() {
    double mag = Norm(); 
    return Vector2f(x / mag, y / mag); 
}

Vector2f Vector2f::Perp() {
    return Vector2f(y, -x); 
}


Vector2f Vector2f::Rotate(double rad) {
    double x2 = std::cos(rad) * x - std::sin(rad) * y; 
    double y2 = std::sin(rad) * x + std::cos(rad) * y; 

    return Vector2f(x2, y2);  
}

Vector2f& Vector2f::operator+=(const Vector2f& rhs) {
    x += rhs.x; 
    y += rhs.y;

    return *this; 
}

Vector2f Vector2f::operator+(const Vector2f& rhs) {
    return Vector2f(x + rhs.x, y + rhs.y); 
}

Vector2f Vector2f::operator-(const Vector2f& rhs) {
    return Vector2f(x - rhs.x, y - rhs.y); 
}

