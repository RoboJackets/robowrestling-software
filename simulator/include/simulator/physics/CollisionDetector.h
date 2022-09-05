#pragma once 

#include "simulator/physics/RigidBody2d.h"
#include "simulator/physics/Vector2f.h" 

#include <utility> 
#include <vector> 

class CollisionDetector {
    
    
    public: 
        virtual ~CollisionDetector() {} 
        virtual std::pair<bool, Vector2f> CheckCollision(RigidBody2d& body1, RigidBody2d& body2) = 0;        
};
