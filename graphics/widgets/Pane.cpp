#include <graphics/widgets/Pane.h>
#include <iostream> 

Pane::Pane(int x, int y, int width, int height, std::string name) {
    _x = x; 
    _y = y; 
    _width = width; 
    _height = height; 
    _name = name;

    _activated = true; 
} 


void Pane::AddWidget(std::shared_ptr<Widget> widget) {
    _widgets.push_back(widget); 
}

void Pane::Render() {
    if (!_activated) {
        return; 
    }

    ImGui::SetNextWindowSize(ImVec2(_width, _height));
    ImGui::SetNextWindowPos(ImVec2(_x, _y)); 
    ImGui::SetNextWindowBgAlpha(_opacity); 
    ImGui::Begin(_name.c_str(), NULL, _flags);
    for (auto widget : _widgets) {
        widget->Render(); 

    }

    ImGui::End(); 


}


void Pane::Activate() {
    _activated = true; 
}

void Pane::Deactivate() {
    _activated = false; 
}

void Pane::SetOpacity(float opacity) {
    _opacity = opacity; 
} 


void Pane::SetFlags(ImGuiWindowFlags flags) {
    _flags = flags; 
}
Pane::~Pane() {



}
