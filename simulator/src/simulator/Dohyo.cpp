#include <simulator/Dohyo.h> 


Dohyo::Dohyo(int x, int y, int radius):_x(x), _y(y), _radius(radius) {

    _cmToPixel = (_radius / (154.0 / 2));
    
    _bodies[0] = std::make_unique<RigidBody2d>(
            RigidBody2d::CreateRobotBody(0.77 - 0.22,(1.54 / 2))); 
    _bodies[1] = std::make_unique<RigidBody2d>(
        RigidBody2d::CreateRobotBody(0.77 + 0.22, (1.54 / 2))); 

    lastTime = std::chrono::system_clock::now(); 

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

    Vector2f f = Vector2f(0.2,0);
    Vector2f r = Vector2f(0.1, 0);
    Vector2f f2(-0.2, 0); 
    Vector2f r2(-0.1, 0); 

    auto now = std::chrono::system_clock::now(); 
    _bodies[0]->ApplyForce(f,r);
    _bodies[1]->ApplyForce(f2,r2);
    _ch.HandleCollision(*_bodies[0], *_bodies[1]);
    _bodies[0]->Update(now - lastTime);
    _bodies[1]->Update(now - lastTime); 
    lastTime = now; 



    for (int i = 0; i < _bodies.size(); i++) {
        auto shape = _bodies[i] -> GetShape(); 
        double width  = (shape.width * 100.0) * _cmToPixel; 
        double height = (shape.height * 100.0) * _cmToPixel; 
        auto [x, y] = _bodies[i] -> GetPos(); 
        x  = (x * 100.0) * _cmToPixel; 
        y  = (y * 100.0) * _cmToPixel;

        //x = x - (width / 2);
        //y = y - (height / 2);


        sf::RectangleShape robot(sf::Vector2f(
                    width * scale, height * scale));

        robot.setFillColor(sf::Color(255, 255 * i, 0)); 
        robot.setOrigin((width * scale) / 2, (height * scale / 2));
        robot.setPosition((x + _x) * scale, ((_radius * 2) - y + _y) * scale);
        robot.setRotation(-(180 / 3.14159) * _bodies[i] -> GetAngle());
        /* draw corners */
        auto corners = _bodies[i]->GetCorners();
        for (auto& corner : corners) {
            sf::CircleShape cornerShape;
            int radius = 5 * scale;  
            cornerShape.setRadius(radius); 
            cornerShape.setFillColor(sf::Color(255,255,255));
            cornerShape.setOrigin(radius/2,radius/2); 
            cornerShape.setPosition((corner.x * 100 * _cmToPixel + _x) * scale - radius/2, ((_radius * 2) - corner.y * 100 * _cmToPixel + _y) * scale - radius/2); 

            window.draw(cornerShape); 
        }

        window.draw(robot); 

        sf::CircleShape center; 
        center.setRadius(10);
        center.setOrigin(5,5); 
        center.setPosition((x + _x) * scale - 5, ((_radius * 2) - y + _y) * scale - 5); 
        center.setFillColor(sf::Color(255, 0, 255));
        window.draw(center); 
    }


}
