#include "graphics/widgets/PlayPauseWidget.h" 


PlayPauseWidget::PlayPauseWidget() {

}


void PlayPauseWidget::Render() {

    /* YOUR CODE HERE */

}

bool PlayPauseWidget::Activated() {
    return true; 
}

std::string PlayPauseWidget::GetName() {
    return "Play/Pause"; 
}

bool PlayPauseWidget::EnableSimulator() {
    return _isEnabled;
}
