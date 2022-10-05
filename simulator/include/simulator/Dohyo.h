#pragma once

#include <SFML/Graphics.hpp>
#include <graphics/Renderable.h>

#include <array>
#include <memory>
#include <iostream>
#include <chrono>

#include <simulator/robots/AdvRobot.h>
#include <simulator/physics/SATCollisionDetector.h>
#include <simulator/physics/CollisionHandler.h>

class Dohyo : public Renderable {
    private:
        int _x;
        int _y;
        int _radius;
        double _cmToPixel;
        std::array<std::unique_ptr<AdvRobot>, 2> _bodies;
        CollisionHandler<SATCollisionDetector> _ch;
        std::chrono::time_point<std::chrono::system_clock> lastTime;

    public:
        Dohyo(int x, int y, int radius);
        void Render(sf::RenderWindow& window, const RenderPoint& point) override;
};
