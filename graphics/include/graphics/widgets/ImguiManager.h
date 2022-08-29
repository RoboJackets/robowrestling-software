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
        double _scale;  
        bool _hasInitialized; 

    public: 
        ImguiManager(double scale = 1);
        ~ImguiManager(); 

        void AddPane(std::shared_ptr<Pane> pane); 
        void Render(sf::Clock &clock, sf::RenderWindow& window);
        void ProcessEvent(sf::Event &event); 
};
