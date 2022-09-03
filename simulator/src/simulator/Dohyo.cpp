#include <simulator/Dohyo.h> 


Dohyo::Dohyo(int x, int y, int radius):_x(x), _y(y), _radius(radius) {

    _cmToPixel = (_radius / (154.0 / 2));
    
    _bodies[0] = std::make_unique<RigidBody2d>(
            RigidBody2d::CreateRobotBody(0.77 - 0.22,(1.54 / 2))); 
    _bodies[1] = std::make_unique<RigidBody2d>(
        RigidBody2d::CreateRobotBody(0.77 + 0.22, (1.54 / 2))); 

}


void Dohyo::Render(sf::RenderWindow& window, const RenderPoint& point) {
    
    double scale = point.scale;

    sf::CircleShape dohyo; 
    dohyo.setRadius(_radius * scale); 
    dohyo.setFillColor(sf::Color(0, 0, 0)); 
    dohyo.setOutlineThickness(2 * scale); 
    dohyo.setOutlineColor(sf::Color(250, 250, 250)); 
    dohyo.setPosition(_x * scale, _y * scale);
    

    /* draw starting lines */
    int centerX = _radius + _x; 
    int centerY = _radius + _y; 
    int lineWidth  = 2 * _cmToPixel;
    int lineHeight = 20 * _cmToPixel;
    int lineDistFromCenter = 10 * _cmToPixel; 
    sf::RectangleShape startLineOne(sf::Vector2f(lineWidth * scale, lineHeight * scale));
    sf::RectangleShape startLineTwo(sf::Vector2f(lineWidth * scale, lineHeight * scale)); 

    startLineOne.setFillColor(sf::Color(255, 69, 0)); 
    startLineTwo.setFillColor(sf::Color(255, 69, 0)); 

    int startLineOneX = centerX - lineDistFromCenter - lineWidth; 
    int startLineTwoX = centerX + lineDistFromCenter; 
    int lineY = centerY - (lineHeight / 2); 
    startLineOne.setPosition((int)(startLineOneX * scale),(int)(lineY * scale));
    startLineTwo.setPosition((int)(startLineTwoX * scale),(int)(lineY * scale)); 
    
    


    window.draw(dohyo);
    window.draw(startLineOne); 
    window.draw(startLineTwo);

    for (int i = 0; i < _bodies.size(); i++) {
        auto shape = _bodies[i] -> GetShape(); 
        double width  = (shape.width * 100.0) * _cmToPixel; 
        double height = (shape.height * 100.0) * _cmToPixel; 
        auto [x, y] = _bodies[i] -> GetPos(); 
        x  = (x * 100.0) * _cmToPixel; 
        y  = (y * 100.0) * _cmToPixel;

        x = x - (width / 2);
        y = y + (height / 2);

        sf::RectangleShape robot(sf::Vector2f(
                    width * scale, height * scale));

        robot.setFillColor(sf::Color(255, 255 * i, 0)); 
        robot.setPosition((x + _x) * scale, ((_radius * 2) - y + _y) * scale);
        window.draw(robot); 
    }


}
