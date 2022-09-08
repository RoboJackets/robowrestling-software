#include <graphics/widgets/ImguiManager.h> 
#include <iostream> 

ImguiManager::ImguiManager(double scale): _scale(scale) {
    
}


void ImguiManager::AddPane(std::shared_ptr<Pane> pane) {
    _panes.push_back(pane); 
}


/** 
 * @brief handles rendering all panes on the screen.
 *
 **/
void ImguiManager::Render(sf::Clock &clock, sf::RenderWindow& window) {
    
    if (!_hasInitialized) {
        ImGui::SFML::Init(window);
        ImGui::StyleColorsDark();
        ImGui::GetStyle().ScaleAllSizes(_scale); 
        ImGui::GetIO().FontGlobalScale = _scale; 
    
        _hasInitialized = true; 
    } else {
      ImGui::SFML::Update(window, clock.restart());
      for (auto pane : _panes) {
          pane->Render();
      }

      ImGui::SFML::Render(window); 
    
    }
}

void ImguiManager::ProcessEvent(sf::Event &event) {
    /* check that imgui is ready to render */
    if (_hasInitialized) {
        ImGui::SFML::ProcessEvent(event);
    }
}


ImguiManager::~ImguiManager() {
    ImGui::SFML::Shutdown(); 

}





