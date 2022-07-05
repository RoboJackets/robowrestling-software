#include "graphics/widgets/FPSWidget.h" 


void FPSWidget::Render() {

    ImGui::Text("FPS: (%.1f)", ImGui::GetIO().Framerate); 
}

bool FPSWidget::Activated() {
    return true; 
}


std::string FPSWidget::GetName() {
    return "FPS Counter"; 
}


