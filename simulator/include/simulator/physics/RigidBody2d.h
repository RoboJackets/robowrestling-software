#pragma once 
#include <chrono> 
#include <stack> 
#include <array> 
#include <memory> 
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

    static BoxShape CreateRobotShape() {
        BoxShape shape; 
        shape.width = 0.2; 
        shape.height = 0.2; 
        shape.mass = 3; 
        shape.momentOfInertia = 0; 

        return shape; 
    }
}; 


/**
 * @brief A class representing a physical object in the shape of a box. 
 *
 */

class RigidBody2d {
    private: 
        Vector2f _pos; 
        Vector2f _vel;
        Vector2f _force; 
        std::stack<AppliedForce> _forces; 

        double _angle;
        double _angularVelocity; 
        double _torque; 

        BoxShape _shape; 
    
    public: 
        RigidBody2d(BoxShape shape); 
        RigidBody2d(double x, double y, BoxShape shape);
        RigidBody2d(double x, double y, double angle, BoxShape shape); 

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


        /**
         * @brief moves the body by some amount, only use as a last resort. 
         *
         * @param x the amount in the x direction to move it.
         * @param y the amount in the y direction to move it. 
         *
         **/
        void Move(double x, double y); 

        /**
         * @brief computes and returns the corners of the rigidbody in world
         * coords. 
         *
         * @return the corners of the body
         *
         **/
        std::array<Vector2f, 4> GetCorners(); 
        double GetAngle();
        double GetTorque(); 
        Vector2f GetPos();
        Vector2f GetVel();
        void SetVel(Vector2f& vel); 
        Vector2f GetForce(); 
        BoxShape GetShape(); 



        /* static factories */

        static RigidBody2d CreateRobotBody(double x = 0, double y = 0, double angle = 0); 

};
