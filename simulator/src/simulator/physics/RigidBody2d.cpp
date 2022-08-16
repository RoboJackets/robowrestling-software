#include "simulator/physics/RigidBody2d.h"
#include <iostream> 

RigidBody2d::RigidBody2d(BoxShape shape) : _pos(Vector2f(0, 0)) {

    _shape = shape; 
    _shape.momentOfInertia = 
        _shape.mass * (_shape.width * _shape.width +
         _shape.height * _shape.height) / 12;

    _vel = Vector2f(0,0); 
}

RigidBody2d::RigidBody2d(double x, double y, BoxShape shape): RigidBody2d(shape) {
    _pos = Vector2f(x,y); 
}

void RigidBody2d::ApplyForce(Vector2f &v, Vector2f &r) {
   AppliedForce af; 
   af.force = v; 
   af.forcePos = r; 
    _forces.push(af);
   _torque += Vector2f::CrossProduct(r, v);
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
}


double RigidBody2d::GetAngle() {
    return _angle; 
}


Vector2f RigidBody2d::GetPos() {
    return _pos; 
}

BoxShape RigidBody2d::GetShape() {
    return _shape;
}

double RigidBody2d::GetTorque() {
    return _torque; 
}
