#pragma once 


#include "graphics/widgets/Widget.h" 



class PlayPauseWidget : public Widget {
    public:
        PlayPauseWidget(); 
        ~PlayPauseWidget(){}
        bool _isEnabled = true; 

        void Render() override; 
        bool Activated() override; 
        std::string GetName() override; 
        
        bool EnableSimulator(); 



}; 
