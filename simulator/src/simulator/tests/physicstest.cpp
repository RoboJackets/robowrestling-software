#include <gtest/gtest.h> 
#include <gmock/gmock.h> 
#include <simulator/physics/Vector2f.h>
#include <simulator/physics/RigidBody2d.h> 

#include <chrono> 
#include <iostream>


using ::testing::Not;
using ::testing::DoubleEq;

namespace PhysicsTests {
    TEST(PhysTest, TestVector2fCTor) {
        double x = 123.321; 
        double y = 453.2543; 
        Vector2f* v; 

        v = new Vector2f(); 
        EXPECT_FLOAT_EQ(0.0, v->x);
        EXPECT_FLOAT_EQ(0.0, v->y);

        delete v; 

        v = new Vector2f(x, y); 
        EXPECT_FLOAT_EQ(x, v->x);
        EXPECT_FLOAT_EQ(y, v->y);
    }


    TEST(PhysTest, TestVectorScale) {
        Vector2f u(10, 10); 
        Vector2f v = u.Scale(2); 

        EXPECT_FLOAT_EQ(v.x, u.x * 2); 
        EXPECT_FLOAT_EQ(v.y, u.y * 2); 
    }

    TEST(PhysTest, TestVectorRotate) {
        Vector2f u(1,0); 

        Vector2f v = u.Rotate(3.14/2); 

        EXPECT_NEAR(1, v.y, 0.01); 

    }

    TEST(PhysTest, TestVectorAdd) {
        double x1 = 432.143;
        double y1 = 765.321; 
        double x2 = 543.4325;
        double y2 = 956.432; 
        Vector2f u(x1,y1);
        Vector2f v(x2,y2); 

        Vector2f w = u + v; 

        EXPECT_FLOAT_EQ(w.x, x1 + x2); 
        EXPECT_FLOAT_EQ(w.y, y1 + y2); 
    }


    TEST(PhysTest, TestVectorSubstract) {
        Vector2f u(10,10); 
        Vector2f v(10,10);

        Vector2f w = u - v; 
        EXPECT_FLOAT_EQ(w.x, 0); 
        EXPECT_FLOAT_EQ(w.y, 0); 
    }

    TEST(PhysTest, TestVectorPlusEqualOp) {
        Vector2f u(12, 12); 
        Vector2f v(15, 13); 

        u += v; 

        EXPECT_FLOAT_EQ(u.x, 27); 
        EXPECT_FLOAT_EQ(u.y, 25) ;
    }


    TEST(PhysTest, TestRigidBodyInit) {
        BoxShape shape; 
        shape.width = 10; 
        shape.height = 10; 
        shape.mass = 1; 
        shape.momentOfInertia = 0; 

        RigidBody2d body(shape); 

        Vector2f pos = body.GetPos(); 
        double angle = body.GetAngle();

        EXPECT_FLOAT_EQ(0, pos.x); 
        EXPECT_FLOAT_EQ(0, pos.y); 
        EXPECT_FLOAT_EQ(0, angle); 
        double moi = (double)200/12; 
        EXPECT_DOUBLE_EQ(moi, body.GetShape().momentOfInertia);
    }

    TEST(PhysTest, TestRigidBodyLinearUpdate){
        BoxShape shape; 
        shape.width = 10; 
        shape.height = 10; 
        shape.mass = 1; 
        shape.momentOfInertia = 0; 

        RigidBody2d body(shape);
        Vector2f f(0,1); 
        Vector2f r(0,5); 
        for (double i = 0; i < 5; i+=0.016) {
            
            body.ApplyForce(f, r); 
            body.Update(duration(0.016));

        }
        
        Vector2f pos = body.GetPos(); 
        EXPECT_NEAR(12.5, pos.y, 0.09); 
    }

    TEST(PhysTest, TestRigidBodyMultipleForces) {
        BoxShape shape; 
        shape.width = 10; 
        shape.height = 10; 
        shape.mass = 1; 
        shape.momentOfInertia = 0; 
        RigidBody2d body(shape); 
        Vector2f f(0,0.5); 
        Vector2f r(5,5);
        Vector2f r2(-5,5); 

        for (double i = 0; i < 5; i+=0.016) {
            body.ApplyForce(f, r); 
            body.ApplyForce(f, r2); 
            body.Update(duration(0.016));
        }

        Vector2f pos = body.GetPos(); 
        EXPECT_NEAR(12.5, pos.y, 0.09);
        EXPECT_NEAR(0, body.GetAngle(), 0.001); 

    } 

    TEST(PhysTest, TestRigidBodyCCWAngularUpdate) {
        BoxShape shape; 
        shape.width = 10; 
        shape.height = 10; 
        shape.mass = 1; 
        shape.momentOfInertia = 0; 
        RigidBody2d body(shape); 
        Vector2f f(0,1); 
        Vector2f r(5,5); 

        for (double i = 0; i < 5; i+=0.016) {
            body.ApplyForce(f, r); 
            body.Update(duration(0.016)); 
        }

        std::cout << body.GetAngle() << std::endl; 

        EXPECT_GT(body.GetAngle(), 0); 
    }

    TEST(PhysTest, TestRigidBodyCWAngularUpdate) {
        BoxShape shape; 
        shape.width = 10; 
        shape.height = 10; 
        shape.mass = 1; 
        shape.momentOfInertia = 0; 
        RigidBody2d body(shape); 
        Vector2f f(0,1); 
        Vector2f r(-5,5); 

        for (double i = 0; i < 5; i+=0.016) {
            body.ApplyForce(f, r); 
            body.Update(duration(0.016)); 
        }

        std::cout << body.GetAngle() << std::endl; 

        EXPECT_LT(body.GetAngle(), 0); 

    }

    /**
     * @brief tests a single force acting on the body not along the center.
     *
     * should rotate and alse end up at a non-zero position
     *
     * */
    TEST(PhysTest, TestRigidBodySingleForce) {
        BoxShape shape; 
        shape.width = 10; 
        shape.height = 10; 
        shape.mass = 1; 
        shape.momentOfInertia = 0; 
        RigidBody2d body(shape); 
        Vector2f f(0,1); 
        Vector2f r(5,-5); 

        for (double i = 0; i < 5; i += 0.016) {
            body.ApplyForce(f, r); 
            body.Update(duration(0.016)); 
        }

        double y = body.GetPos().y; 
        double x = body.GetPos().x;
        std::cout << "x: " << x << ", y: " << y << std::endl; 
        EXPECT_THAT(x, Not(DoubleEq(0)));

        
    }

} 
