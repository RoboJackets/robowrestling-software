#include <gtest/gtest.h> 

#include <simulator/physics/Vector2f.h> 
#include <simulator/physics/RigidBody2d.h> 

#include <simulator/physics/SATCollisionDetector.h>


#include <chrono>
#include <iostream> 
#include <memory> 

namespace {
    class SATCollisionTest : public ::testing::Test {
        protected: 
            std::unique_ptr<RigidBody2d> bodyOne; 
            std::unique_ptr<RigidBody2d> bodyTwo; 

            SATCollisionDetector detector;

            void SetUp() override {
                bodyOne = std::make_unique<RigidBody2d>(RigidBody2d::CreateRobotBody()); 
                bodyTwo = std::make_unique<RigidBody2d>(RigidBody2d::CreateRobotBody(3,0));

            }
    };


    TEST_F(SATCollisionTest, TestDirectCollisionX) {
        Vector2f f(1,0); 
        Vector2f r(0.2, 0); 

        bool collided = false; 
        for (double i = 0; i < 6.0; i += 0.016) {
            bodyOne -> ApplyForce(f, r); 
            bodyOne -> Update(duration(0.016)); 

            auto[hasCollided, mtv] = detector.CheckCollision(*bodyOne, *bodyTwo);
            collided = hasCollided;
            std::cout << "x: " << mtv.x << ", y: " << mtv.y << std::endl; 
            if (collided) 
                break; 
        }

        EXPECT_EQ(collided, true); 
    }


    TEST_F(SATCollisionTest, TestDirectCollisionY) {
        bodyTwo = std::make_unique<RigidBody2d>(RigidBody2d::CreateRobotBody(0,3)); 

        Vector2f f(0,1); 
        Vector2f r(0, 0.2); 

        bool collided = false; 
        for (double i = 0; i < 6.0; i += 0.016) {
            bodyOne -> ApplyForce(f, r); 
            bodyOne -> Update(duration(0.016)); 

            auto [hasCollided, mtv] = detector.CheckCollision(*bodyOne, *bodyTwo);
            collided = hasCollided;
            auto [x, y] = bodyOne -> GetPos(); 
            std::cout << "x: " << mtv.x << ", y: " << mtv.y << std::endl; 

            if (collided) 
                break; 
        }
        
        EXPECT_EQ(collided, true);
    }

    TEST_F(SATCollisionTest, TestAngledCollisionX) {
        bodyTwo = std::make_unique<RigidBody2d>(RigidBody2d::CreateRobotBody(3, 0, 3.14 / 4));
        

        Vector2f f(1,0); 
        Vector2f r(0.2, 0); 

        bool collided = false; 
        for (double i = 0; i < 6.0; i += 0.016) {
            bodyOne -> ApplyForce(f, r); 
            bodyOne -> Update(duration(0.016)); 

            auto [hasCollided, mtv] = detector.CheckCollision(*bodyOne, *bodyTwo);
            collided = hasCollided;
            auto [x, y] = bodyOne -> GetPos(); 
            std::cout << "x: " << mtv.x << ", y: " << mtv.y << std::endl; 

            if (collided) 
                break; 
        }
        
        EXPECT_EQ(collided, true);

    }
}
