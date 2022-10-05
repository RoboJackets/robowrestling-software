#include <simulator/Dohyo.h>

Dohyo::Dohyo(int x, int y, int radius) : _x(x), _y(y), _radius(radius)
{

    _cmToPixel = (_radius / (154.0 / 2));

    _bodies[0] = std::make_unique<AdvRobot>(0.77 - 0.22, (1.54 / 2), 0.0, radius);
    _bodies[1] = std::make_unique<AdvRobot>(0.77 + 0.22, (1.54 / 2), 0.0, radius);

    lastTime = std::chrono::system_clock::now();
}

void Dohyo::Render(sf::RenderWindow &window, const RenderPoint &point)
{
    double scale = point.scale;

    // draw dohyo
    sf::CircleShape dohyo;
    dohyo.setRadius(_radius * scale);
    dohyo.setFillColor(sf::Color(0, 0, 0));
    dohyo.setOutlineThickness(2 * scale);
    dohyo.setOutlineColor(sf::Color(250, 250, 250));
    dohyo.setPosition(_x * scale, _y * scale);

    /* draw starting lines */
    int centerX = _radius + _x;
    int centerY = _radius + _y;
    int lineWidth = 2 * _cmToPixel;
    int lineHeight = 20 * _cmToPixel;
    int lineDistFromCenter = 10 * _cmToPixel;
    sf::RectangleShape startLineOne(sf::Vector2f(lineWidth * scale, lineHeight * scale));
    sf::RectangleShape startLineTwo(sf::Vector2f(lineWidth * scale, lineHeight * scale));

    startLineOne.setFillColor(sf::Color(255, 69, 0));
    startLineTwo.setFillColor(sf::Color(255, 69, 0));

    int startLineOneX = centerX - lineDistFromCenter - lineWidth;
    int startLineTwoX = centerX + lineDistFromCenter;
    int lineY = centerY - (lineHeight / 2);
    startLineOne.setPosition((int)(startLineOneX * scale), (int)(lineY * scale));
    startLineTwo.setPosition((int)(startLineTwoX * scale), (int)(lineY * scale));

    window.draw(dohyo);
    window.draw(startLineOne);
    window.draw(startLineTwo);

    // physics
    Vector2f f = Vector2f(0.2, 0);
    Vector2f r = Vector2f(0.1, 0);
    Vector2f f2(-0.2, 0);
    Vector2f r2(-0.1, 0);

    auto now = std::chrono::system_clock::now();
    _bodies[0]->body_->ApplyForce(f, r);
    _bodies[1]->body_->ApplyForce(f2, r2);
    _ch.HandleCollision(*(_bodies[0]->body_), *(_bodies[1]->body_));
    _bodies[0]->body_->Update(now - lastTime);
    _bodies[1]->body_->Update(now - lastTime);
    lastTime = now;

    // render robots
    for (int i = 0; i < _bodies.size(); i++)
    {
        _bodies[i]->Render(window, *(new RenderPoint(_x, _y, scale)));
    }
}
