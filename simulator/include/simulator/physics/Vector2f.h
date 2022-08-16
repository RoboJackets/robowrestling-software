#pragma once 

#include <cmath>
/**
 * @brief struct representing a vector in two dimensional space. 
 * 
 */
struct Vector2f {
    public: 
        double x; 
        double y;

        Vector2f(); 
        Vector2f(double x ,double y);


        /**
         * @brief computes the cross product of a vector with the current vector.
         * 
         * @param u the first vector to compute the cross product of
         * @param v the second vector the compute the cross product of
         * @return double the cross product 
         */
        static double CrossProduct(const Vector2f &u, const Vector2f &v); 


        /**
         * @brief scales the current vector by some factor 
         *
         * @param factor the factor to scale the vector by
         * @return Vector2f the scaled vector
         */
        Vector2f Scale(const double factor);
        

        double Norm(); 


        /**
         * @brief rotates the current vector around its tail a certain amount 
         * of radians. 
         *
         * @param the radians to rotate the vector 
         * @return the rotated vector
         **/
        Vector2f Rotate(double rad);



        /* Operator overloads */

        Vector2f& operator+=(const Vector2f& rhs); 
        Vector2f  operator+(const Vector2f& rhs); 
        Vector2f  operator-(const Vector2f& rhs); 

}; 
