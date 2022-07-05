#pragma once 

#include "imgui.h" 
#include "imgui-SFML.h"
#include "SFML/Graphics.hpp"

#include <vector> 
#include <memory> 
#include <graphics/widgets/Pane.h> 
class ImguiManager {

    private: 
        std::vector<std::shared_ptr<Pane>> _panes; 
        std::shared_ptr<sf::RenderWindow> _window; 
        ImGuiIO* _io; 

    public: 
        ImguiManager(std::shared_ptr<sf::RenderWindow> window, float scale);
        ~ImguiManager(); 

        void AddPane(std::shared_ptr<Pane> pane); 
        void Render(sf::Clock &clock);
        void ProcessEvent(sf::Event &event); 
};
