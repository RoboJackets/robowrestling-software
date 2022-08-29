#pragma once 

#include <SFML/Graphics.hpp> 
#include <functional> 


class Renderable {
     
    
    public: 
        virtual ~Renderable() {}
        virtual void Render(sf::RenderWindow& window, double scale) = 0; 
}; 


class AdHocRenderable : public Renderable {

    private: 
        std::function<void(sf::RenderWindow&, double)> _render; 

    public: 
        explicit AdHocRenderable(std::function<void(sf::RenderWindow&, double)> f) :
            _render(std::move(f)) {} 

        void Render(sf::RenderWindow& window, double scale) override {
            _render(window, scale); 
        }
};
