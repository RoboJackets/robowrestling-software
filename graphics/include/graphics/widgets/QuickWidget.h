#pragma once 

#include <functional> 
#include "graphics/widgets/Widget.h" 


class QuickWidget : public Widget {
    private: 
        std::function<void()> _renderCallback; 
        std::function<bool()> _activatedCallback; 
        std::function<std::string()> _getNameCallback; 

    public: 
        void Render() override; 
        bool Activated() override; 
        std::string GetName() override;


        void SetRenderCallback(std::function<void()> render);
        void SetActivatedCallback(std::function<bool()> activated); 
        void SetGetNameCallback(std::function<std::string()> getName); 


};
