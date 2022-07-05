#include "graphics/widgets/QuickWidget.h" 


void QuickWidget::Render() {
    _renderCallback(); 
} 


bool QuickWidget::Activated() {
   return _activatedCallback(); 
}

std::string QuickWidget::GetName(){
   return _getNameCallback(); 
}


void QuickWidget::SetRenderCallback(std::function<void()> render){
   _renderCallback = render;  
}

void QuickWidget::SetActivatedCallback(std::function<bool()> activated) {
    _activatedCallback = activated;
}

void QuickWidget::SetGetNameCallback(std::function<std::string()> getName) {
    _getNameCallback = getName; 
}
