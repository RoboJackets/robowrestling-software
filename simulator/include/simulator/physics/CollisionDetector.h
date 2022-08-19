#pragma once 

#include "simulator/physics/RigidBody2d.h"

class CollisionDetector {
    
    
    public: 
        virtual ~CollisionDetector() {} 
        virtual bool CheckCollision(RigidBody2d body1, RigidBody2d body2) = 0;        
};
