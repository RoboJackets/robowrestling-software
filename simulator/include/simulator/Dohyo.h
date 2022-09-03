#pragma once 

#include <SFML/Graphics.hpp> 
#include <graphics/Renderable.h> 

#include <array> 
#include <memory> 
#include <iostream> 
#include <chrono> 

#include <simulator/physics/RigidBody2d.h> 
#include <simulator/physics/SATCollisionDetector.h>

class Dohyo : public Renderable {
    private: 
        int _x; 
        int _y; 
        int _radius;
        double _cmToPixel;
        std::array<std::unique_ptr<RigidBody2d>, 2> _bodies; 
        bool collided = false; 
        SATCollisionDetector detector; 

    public: 
        Dohyo(int x, int y, int radius); 
        void Render(sf::RenderWindow& window, const RenderPoint& point) override; 
};
