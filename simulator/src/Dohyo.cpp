#include <simulator/Dohyo.h> 


Dohyo::Dohyo(int x, int y, int radius):_x(x), _y(y), _radius(radius) {

    _cmToPixel = (_radius / 154.0);
    
}


void Dohyo::Dohyo(sf::RenderWindow& window, double scale) {
    sf::CircleShape dohyo; 
    dohyo.setRadius(_radius * scale) ;
    dohyo.setFillColor(sf::Color(0, 0, 0)); 
    dohyo.setOutlineThickness(2 * scale); 
    dohyo.setOutlineColor(sf::Color(250, 250, 250)); 
    dohyo.setPosition(_x * scale, _y * scale);
    
    window.draw(dohyo); 
}
