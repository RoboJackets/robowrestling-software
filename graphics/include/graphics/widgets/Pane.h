#pragma once 

#include <imgui.h> 
#include <memory> 
#include <vector> 
#include <string> 
#include <graphics/widgets/Widget.h> 


class Window; 

/**
 * Manages and renders widgets onto panes on the screen. 
 *
 *
 */
class Pane {
    private: 
        int _x; 
        int _y; 
        int _width; 
        int _height;
        float _opacity = 1; 
        bool _activated; 
        std::string _name; 
        std::vector<std::shared_ptr<Widget>> _widgets; 
        ImGuiWindowFlags _flags; 

        friend class Window; 


    public: 
        Pane(int x, int y, int width, int height, std::string name); 
        ~Pane(); 

        void Render(); 
        void AddWidget(std::shared_ptr<Widget> widget); 
        void Activate(); 
        void Deactivate(); 
        void SetOpacity(float opacity); 
        void SetFlags(ImGuiWindowFlags flags); 

};
