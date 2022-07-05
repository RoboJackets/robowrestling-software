#pragma once 

#include "graphics/widgets/Widget.h" 
 

class FPSWidget : public Widget {
    public: 
        FPSWidget(){}
        ~FPSWidget(){}
        void Render() override; 
        bool Activated() override; 
        std::string GetName() override; 


};
