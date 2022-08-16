#pragma once 
#include <chrono> 
#include <stack> 
#include "simulator/physics/Vector2f.h"

using duration = std::chrono::duration<double>;

struct AppliedForce {
    Vector2f force; 
    Vector2f forcePos; 
};

struct BoxShape {
    double width; 
    double height; 
    double mass; 
    double momentOfInertia; 
}; 


/**
 * @brief A class representing a physical object in the shape of a box. 
 *
 */

class RigidBody2d {
    private: 
        Vector2f _pos; 
        Vector2f _vel; 
        std::stack<AppliedForce> _forces; 

        double _angle;
        double _angularVelocity; 
        double _torque; 

        BoxShape _shape; 
    
    public: 
        RigidBody2d(BoxShape shape); 
        RigidBody2d(double x, double y, BoxShape shape);

        /**
         * @brief applys a force at some vector r away from the center of the 
         * body
         *
         * @param v the force vector to apply to the body 
         * @param r the pos relative to the center of the body to apply the 
         * force
         */
        void ApplyForce(Vector2f &v, Vector2f &r);
        

        /**
         * @brief Updates the body with the applied forces. 
         * The forces are cleared every update 
         *
         * @param delta the amount of time that has elapsed since the last update.
         */
        void Update(duration delta);


        double GetAngle();
        double GetTorque(); 
        Vector2f GetPos();
        BoxShape GetShape(); 





};
