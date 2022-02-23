#include <iostream>
#include <memory>
#include "screen.h"

#include <SFML/Graphics/Text.hpp>

class StartMenu : public Screen {
    private:
		std::shared_ptr<sf::RenderWindow> window_;
		sf::Text title;
		sf::Text play_button;
		sf::Text exit_button;
		sf::Text config_button;

		bool title_selected;
		bool title_pressed;
		bool play_selected;
		bool play_pressed;
		bool exit_selected;
		bool exit_pressed;
		bool config_selected;
		bool config_pressed;

		int option = 0;
		const int NUM_BUTTONS = 3;
    public:
	    StartMenu(std::shared_ptr<sf::RenderWindow> App);
	    void Init();
		void Draw();
		void ProcessInput();
		void Update();
};

