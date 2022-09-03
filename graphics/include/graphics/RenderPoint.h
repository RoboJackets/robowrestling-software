#pragma once 


/**
 * defines a point to use as a reference for use when rendering to the window. 
 **/
struct RenderPoint {
    
    const int x; 
    const int y; 
    const double scale; 

    RenderPoint(int x = 0, int y = 0, double scale = 1.0) : x(x), y(y), scale(scale) {}



};  
