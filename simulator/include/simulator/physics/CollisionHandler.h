#pragma once 

#include "simulator/physics/CollisionDetector.h"
#include "simulator/physics/RigidBody2d.h" 
#include <iostream> 

template <class CD> 
class CollisionHandler {
    private: 
        CD collisionDetector; 

    public:
        void HandleImpulse(RigidBody2d& body1, RigidBody2d& body2, Vector2f& norm) {
            Vector2f vel1 = body1.GetVel(); 
            Vector2f vel2 = body2.GetVel(); 

            Vector2f velRelative = vel2 - vel1; 
            double velNorm = Vector2f::DotProduct(velRelative, norm); 
            
            double mass1 = body1.GetShape().mass; 
            double mass2 = body2.GetShape().mass; 

            double impulse = velNorm / (mass1 + mass2); 

            Vector2f vel1Prime = vel1 + norm.Scale(impulse / mass1); 
            Vector2f vel2Prime = vel2 - norm.Scale(impulse / mass2);
            

            body1.SetVel(vel1Prime); 
            body2.SetVel(vel2Prime); 
        }

        Vector2f ProcessCollision(RigidBody2d& body1, RigidBody2d& body2) {
            auto [collided, mtv] = collisionDetector.CheckCollision(body1, body2); 
            if (!collided)
                return Vector2f(0,0); 
            /* if the bodies have collided, apply the correct force to each */
            auto body1Pos = body1.GetPos(); 
            auto body2Pos = body2.GetPos();

            std::array<Vector2f, 4> body1Corners = body1.GetCorners(); 
            std::array<Vector2f, 4> body2Corners = body2.GetCorners(); 

            Vector2f body1Force = body1.GetForce(); 
            Vector2f body2Force = body2.GetForce(); 

            Vector2f distance = body2Pos - body1Pos; 



            /* translate for world coords to local coords */
            std::transform(body1Corners.begin(), body1Corners.end(), body1Corners.begin(), 
                    [&body1Pos](Vector2f &u) {
                    return u - body1Pos; 
            });  
            
            std::transform(body2Corners.begin(), body2Corners.end(), body2Corners.begin(), 
                    [&body2Pos](Vector2f &u) {
                    return u - body2Pos; 
            });
            /* figure out which corner, or corners, are closest to the other
             * body */
            std::vector<Vector2f> body1ToBody2; 
            std::vector<Vector2f> body2ToBody1; 

            Vector2f nDistance = distance.Normalize();
            std::sort(body1Corners.begin(), body1Corners.end(), 
                    [&nDistance] (Vector2f& a, Vector2f& b){

                    double aDot = Vector2f::DotProduct(a, nDistance); 
                    double bDot = Vector2f::DotProduct(b, nDistance); 

                    return aDot > bDot; 
            }); 

            Vector2f nReversedDistance = nDistance.Scale(-1);
            std::sort(body2Corners.begin(), body2Corners.end(), 
                    [&nReversedDistance] (Vector2f& a, Vector2f& b){

                    double aDot = (Vector2f::DotProduct(a, nReversedDistance)); 
                    double bDot = (Vector2f::DotProduct(b, nReversedDistance)); 
                    

                    return aDot > bDot; 
            }); 

            double minDot = Vector2f::DotProduct(body1Corners[0], nDistance); 
            for (auto& v: body1Corners) {
                if (Vector2f::DotProduct(v, nDistance) == minDot) {
                    body1ToBody2.push_back(v + body1Pos); 
                }
            }

             
            minDot = Vector2f::DotProduct(body2Corners[0], nReversedDistance);
            for (auto& v: body2Corners) {
                if (Vector2f::DotProduct(v, nReversedDistance) == minDot) {
                    body2ToBody1.push_back(v + body2Pos); 
                }
            } 

            std::vector<Vector2f> contactManifold;
            /* compute contact points */
            contactManifold.reserve(body1ToBody2.size() + body2ToBody1.size());
            contactManifold.insert(contactManifold.end(), body1ToBody2.begin(), body1ToBody2.end()); 
            contactManifold.insert(contactManifold.end(), body2ToBody1.begin(), body2ToBody1.end()); 

            for (auto v : contactManifold) {
            
            }

            std::cout << "\n" << std::endl; 

           // an vertex is primary contact point, no need to distribute force
           // if (body1ToBody2.size() == 1 || body1ToBody2.size() == 1) { 
           //     Vector2f r = body1ToBody2[0] - body2Pos; 
           //     body2.ApplyForce(body1Force, r); 
           // } else {
                // distribute force across contact points 
                Vector2f norm = mtv.Normalize().Scale(-1); 
                for (auto& v: contactManifold) {
                    Vector2f r = v - body2Pos;
                    Vector2f r2 = v - body1Pos; 
                    Vector2f f = norm.Scale(body1Force.Norm() / contactManifold.size()); 
                    //Vector2f f = body1Force.Scale((double) 1 / contactManifold.size()); 
                
                    Vector2f f2 = f.Scale(-1); 

                    body2.ApplyForce(f, r);
                    body1.ApplyForce(f2, r2); 

                } 
           //}
            
            /* move objects out of penetration till they are just touching */
            Vector2f minMove = body1Force.Normalize().Scale(mtv.Norm()); 
            
            body1.Move(mtv.x, mtv.y); 
            return mtv.Normalize().Scale(-1); 

        }

        void HandleCollision(RigidBody2d& body1, RigidBody2d& body2) {
            Vector2f norm = ProcessCollision(body1, body2); 
            //ProcessCollision(body2, body1); 
            
            if (!(norm.x == 0 && norm.y == 0)) {
                // collision occurred 
                HandleImpulse(body1, body2, norm); 

    
            }


        } 
};
