#include <graphics/widgets/ImguiManager.h> 
#include <iostream> 

ImguiManager::ImguiManager(std::shared_ptr<sf::RenderWindow> window, float scale) {
    _window = window; 

    
    /* Set up Imgui */

    ImGui::SFML::Init(*_window.get());

    ImGui::StyleColorsDark();
    ImGui::GetStyle().ScaleAllSizes(scale); 
    ImGui::GetIO().FontGlobalScale = scale; 


    
}


void ImguiManager::AddPane(std::shared_ptr<Pane> pane) {
    _panes.push_back(pane); 
}


/** 
 * handles rendering all panes on the screen.
 *
 * TODO abstract depends on SDL2 backend, abstract away 
 **/
void ImguiManager::Render(sf::Clock &clock) {
    ImGui::SFML::Update(*_window.get(), clock.restart());
    for (auto pane : _panes) {
        pane->Render();
    }

    ImGui::SFML::Render(*_window.get());
}

void ImguiManager::ProcessEvent(sf::Event &event) {
    ImGui::SFML::ProcessEvent(event);
}


ImguiManager::~ImguiManager() {
    ImGui::SFML::Shutdown(); 

}





