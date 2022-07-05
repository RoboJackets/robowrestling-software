#pragma once 


#include <imgui.h> 
#include <string> 

/**
 * abstract class for a widget, likely made using imgui. 
 *
 */
class Widget {
    public:
        virtual void Render() = 0; 
        virtual bool Activated() = 0; 
        virtual std::string GetName() = 0; 
        
        virtual ~Widget() {} 

}; 
