#pragma once 

#include <SFML/Graphics.hpp>
#include <graphics/RenderPoint.h> 
#include <memory> 
#include <functional> 


class Renderable {
     
    
    public: 
        virtual ~Renderable() {}
        virtual void Render(sf::RenderWindow& window, const RenderPoint& point) = 0; 
}; 


class AdHocRenderable : public Renderable {

    private: 
        std::function<void(sf::RenderWindow&, const RenderPoint& point)> _render; 

    public: 
        explicit AdHocRenderable(std::function<void(sf::RenderWindow&, const RenderPoint& point)> f) :
            _render(std::move(f)) {} 

        void Render(sf::RenderWindow& window, const RenderPoint& point) override {
            _render(window, point); 
        }
};
