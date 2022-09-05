#include "simulator/physics/RigidBody2d.h"
#include <iostream> 

RigidBody2d::RigidBody2d(BoxShape shape) : _pos(Vector2f(0, 0)) {

    _shape = shape; 
    _shape.momentOfInertia = 
        _shape.mass * (_shape.width * _shape.width +
         _shape.height * _shape.height) / 12;

    _vel = Vector2f(0,0);
    _force = Vector2f(0,0); 
}

RigidBody2d::RigidBody2d(double x, double y, BoxShape shape): RigidBody2d(shape) {
    _pos = Vector2f(x,y); 
}

RigidBody2d::RigidBody2d(double x, double y, double angle, BoxShape shape): RigidBody2d(x, y, shape) {
    _angle = angle; 
}

void RigidBody2d::ApplyForce(Vector2f &v, Vector2f &r) {
   

    AppliedForce af;
    _force += v.Rotate(_angle); 
    af.force = v; 
    af.forcePos = r; 
    _forces.push(af);
    _torque += Vector2f::CrossProduct(r, v);
}

std::array<Vector2f, 4> RigidBody2d::GetCorners() {
    std::array<Vector2f, 4> corners;
    
    double width = _shape.width; 
    double height = _shape.height;
    
    /* starting at the top right corner and going counter clockwise */
    /* these are relative to the body */

    corners[0] = Vector2f(width / 2, height / 2); 
    corners[1] = Vector2f(-width / 2, height / 2); 
    corners[2] = Vector2f(-width / 2, -height / 2); 
    corners[3] = Vector2f(width / 2, -height /2); 


    /* translate and rotate to world coords */
    for (int i = 0; i < corners.size(); i++) {
        Vector2f rotatedBodyCorner = corners[i].Rotate(_angle); 
        Vector2f worldVector = rotatedBodyCorner + _pos; 

        corners[i] = worldVector;
    }

    return corners; 
} 

void RigidBody2d::Update(duration delta) {
   
    while (!_forces.empty()) {
        AppliedForce af = _forces.top(); 
        _forces.pop();

        /* compute accel relative to the body */
        Vector2f linAccel = 
            Vector2f(af.force.x / _shape.mass, af.force.y / _shape.mass);

        /* rotate the accel to make it relative to world */
        Vector2f accel = linAccel.Rotate(_angle); 
        Vector2f dv = accel.Scale(delta.count()); 

        _vel += dv;

         
    }
    Vector2f ds = _vel.Scale(delta.count());     
    _pos += ds; 

    double angularAccel = _torque / _shape.momentOfInertia;
    _angularVelocity += angularAccel * delta.count(); 
    _angle += _angularVelocity * delta.count();

    _torque = 0.0;
    _force = Vector2f(0,0);
}

void RigidBody2d::Move(double x, double y) {
    _pos += Vector2f(x,y); 
}

double RigidBody2d::GetAngle() {
    return _angle; 
}


Vector2f RigidBody2d::GetPos() {
    return _pos; 
}

Vector2f RigidBody2d::GetVel() {
    return _vel; 
}

void RigidBody2d::SetVel(Vector2f& vel) {
    _vel = vel; 
}

Vector2f RigidBody2d::GetForce() {
    return _force; 
}

BoxShape RigidBody2d::GetShape() {
    return _shape;
}

double RigidBody2d::GetTorque() {
    return _torque; 
}


RigidBody2d RigidBody2d::CreateRobotBody(double x, double y, double angle) {
    BoxShape shape = BoxShape::CreateRobotShape(); 
     
    RigidBody2d body(x, y, angle, shape); 

    return body; 
}
