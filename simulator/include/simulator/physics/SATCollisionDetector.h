#pragma once 

#include <array> 
#include <algorithm> 
#include <functional> 
#include <utility> 
#include <limits> 
#include <algorithm> 
#include "simulator/physics/CollisionDetector.h"


/**
 * @brief A Collision Detector that uses The Seperate Axis Theorem to determine 
 * if two bodies are colliding. 
 **/
class SATCollisionDetector : public CollisionDetector {

    /**
     * @brief finds the unique normal axes for both body1 and body 2. 
     *
     * @param body1 the first body being tested for collision. 
     * @param body2 the second body being tested for collision. 
     *
     * @return an array that contains the unique normal axes. 
     **/
    std::array<Vector2f, 4> GetAxes(RigidBody2d& body1, RigidBody2d& body2);
    
    /**
     * @brief gets the sides of a rigidbody by using its corner vectors. 
     * only gets 2 of the sides because only two are needed to find the normal
     * axes.
     *
     * @param body the body to get the sides of. 
     *
     * @return an array of the sides of the rigidbody. 
     **/
    std::array<Vector2f, 2> GetBodySides(RigidBody2d& body);
    
    /**
     * @brief gets the minimum and maximum projections of a rigidbody on a 
     * axis. 
     *
     * @param axis the axis to project on to. 
     * @param body the body to be projected. 
     *
     * @return the minimum and maximum of body over the axis. 
     **/
    std::pair<double, double> GetBounds(Vector2f axis, RigidBody2d& body); 
    
    public: 
        ~SATCollisionDetector() {}

        /**
         * @brief checks if two bodies have collided using Seperate Axis Theorem.
         *
         * @param body1 a rigidbody 
         * @param body2 a rigidbody to check against body1 
         *
         * @return whether or not bodies have collided
         **/
        std::pair<bool, Vector2f> CheckCollision(RigidBody2d& body1, RigidBody2d& body2) override; 
};
