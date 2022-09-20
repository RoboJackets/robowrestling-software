#pragma once 


#include "graphics/widget/Widget.h" 



class PlayPauseWidget : public Widget {
    public:
        PlayPauseWidget(); 
        ~PlayPauseWidget(){}
        bool _isEnabled = true; 

        void Render() override; 
        bool Activated() override; 
        std::string GetName() override; 
        
        bool EnableSimulator(); 



} 
