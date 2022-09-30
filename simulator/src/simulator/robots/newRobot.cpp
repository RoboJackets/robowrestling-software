#include <simulator/robots/newRobot.h>
#include <strategy/slammywhammy.h>

NewRobot::NewRobot(double x, double y, double angle, int dohyoRadius) {

    body_ = std::make_unique<RigidBody2d>(
            RigidBody2d::CreateRobotBody(x, y, angle)
        );

    _cmToPixel = (dohyoRadius / (154.0 / 2));
    _radius = dohyoRadius;

    // other vars for wheels, etc
	strat_ = std::make_unique<SlammyWhammy>();
}

void NewRobot::Render(sf::RenderWindow& window, const RenderPoint& point) {
    double scale = point.scale;

    auto shape = body_->GetShape();
    double width  = (shape.width * 100.0) * _cmToPixel;
    double height = (shape.height * 100.0) * _cmToPixel;
    auto [x, y] = body_->GetPos();
    x  = (x * 100.0) * _cmToPixel;
    y  = (y * 100.0) * _cmToPixel;

    //x = x - (width / 2);
    //y = y - (height / 2);


    sf::RectangleShape robot(sf::Vector2f(
                width * scale, height * scale));

    robot.setFillColor(sf::Color(89, 86, 78));
    robot.setOrigin((width * scale) / 2, (height * scale / 2));
    robot.setPosition((x + point.x) * scale, ((_radius * 2) - y + point.y) * scale);
    robot.setRotation(-(180 / 3.14159) * body_-> GetAngle());

    window.draw(robot);
    
    /* draw corners */
    auto corners = body_->GetCorners();
    for (auto& corner : corners) {
        sf::CircleShape cornerShape;
        int radius = 5 * scale;
        cornerShape.setRadius(radius);
        cornerShape.setFillColor(sf::Color(255,255,255));
        cornerShape.setOrigin(radius/2,radius/2);
        cornerShape.setPosition((corner.x * 100 * _cmToPixel + point.x) * scale - radius/2, ((_radius * 2) - corner.y * 100 * _cmToPixel + point.y) * scale - radius/2);

        window.draw(cornerShape);
    }

    sf::CircleShape center;
    center.setRadius(10);
    center.setOrigin(5,5);
    center.setPosition((x + point.x) * scale - 5, ((_radius * 2) - y + point.y) * scale - 5);
    center.setFillColor(sf::Color(255, 0, 255));
    window.draw(center);
}

